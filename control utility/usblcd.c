#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* this is libusb, see http://libusb.sourceforge.net/ */
#include <usb.h>

// So far, we assume the user has perfect syntax. Not a robust program.
// User commands
#define LCD_OFF 0
#define LCD_ON 	1
#define LCD_CLR 2
#define FAN1 	3
#define FAN2	4
#define LIGHTS  5

// For user, send string; for AVR, publish string to line.
#define LCDALN0 6
#define LCDALN1 7
#define LCDBLN0 8
#define LCDBLN1 9

// commands for string communication
#define BEGIN_TRANSMIT 	10
#define SEND_CHAR		11
#define ESCAPE_CHAR		126

/* Used to get descriptor strings for device identification */
static int usbGetDescriptorString(usb_dev_handle *dev, int index, int langid, 
                                  char *buf, int buflen) {
    char buffer[256];
    int rval, i;

	// make standard request GET_DESCRIPTOR, type string and given index 
    // (e.g. dev->iProduct)
	rval = usb_control_msg(dev, 
        USB_TYPE_STANDARD | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 
        USB_REQ_GET_DESCRIPTOR, (USB_DT_STRING << 8) + index, langid, 
        buffer, sizeof(buffer), 1000);
        
    if(rval < 0) // error
		return rval;
	
    // rval should be bytes read, but buffer[0] contains the actual response size
	if((unsigned char)buffer[0] < rval)
		rval = (unsigned char)buffer[0]; // string is shorter than bytes read
	
	if(buffer[1] != USB_DT_STRING) // second byte is the data type
		return 0; // invalid return type
		
	// we're dealing with UTF-16LE here so actual chars is half of rval,
	// and index 0 doesn't count
	rval /= 2;
	
	/* lossy conversion to ISO Latin1 */
	for(i = 1; i < rval && i < buflen; i++) {
		if(buffer[2 * i + 1] == 0)
			buf[i-1] = buffer[2 * i];
		else
			buf[i-1] = '?'; /* outside of ISO Latin1 range */
	}
	buf[i-1] = 0;
	
	return i-1;
}

static usb_dev_handle * usbOpenDevice(int vendor, char *vendorName, 
                                      int product, char *productName) {
	struct usb_bus *bus;
	struct usb_device *dev;
	char devVendor[256], devProduct[256];
    
	usb_dev_handle * handle = NULL;
	
	usb_init();
	usb_find_busses();
	usb_find_devices();
	
	for(bus=usb_get_busses(); bus; bus=bus->next) {
		for(dev=bus->devices; dev; dev=dev->next) {			
			if(dev->descriptor.idVendor != vendor ||
               dev->descriptor.idProduct != product)
                continue;
                
            /* we need to open the device in order to query strings */
            if(!(handle = usb_open(dev))) {
                fprintf(stderr, "Warning: cannot open USB device: %s\n",
                    usb_strerror());
                continue;
            }
            
            /* get vendor name */
            if(usbGetDescriptorString(handle, dev->descriptor.iManufacturer, 0x0409, devVendor, sizeof(devVendor)) < 0) {
                fprintf(stderr, 
                    "Warning: cannot query manufacturer for device: %s\n", 
                    usb_strerror());
                usb_close(handle);
                continue;
            }
            
            /* get product name */
            if(usbGetDescriptorString(handle, dev->descriptor.iProduct, 
               0x0409, devProduct, sizeof(devVendor)) < 0) {
                fprintf(stderr, 
                    "Warning: cannot query product for device: %s\n", 
                    usb_strerror());
                usb_close(handle);
                continue;
            }
            
            if(strcmp(devVendor, vendorName) == 0 && 
               strcmp(devProduct, productName) == 0)
                return handle;
            else
                usb_close(handle);
		}
	}
	
	return NULL;
}

int main(int argc, char **argv) {
	usb_dev_handle *handle = NULL;
    int nBytes = 0;
    char buffer[256];

	if(argc > 3) {
		printf("Usage:\n");
		printf("usbtext.exe <LED#> <1:on, 0:off>\n");
		exit(1);
	}
	
	handle = usbOpenDevice(0x16C0, "amcnicoll", 0x05DC, "USBLCD");
	
	if(handle == NULL) {
		fprintf(stderr, "Could not find USB device!\n");
		exit(1);
	}

	// If user command is the same as AVR command, just pass it on.
	if(atoi(argv[1])<=5){
		nBytes = usb_control_msg(handle, 
			USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 
			atoi(argv[1]), atoi(argv[2]), 0, (char *)buffer, sizeof(buffer), 5000);
			printf("Values passed on.");
	}
	
	// If the command is to send a string, we have to decode it and send it piece by piece.
	else {
		// Decode string into uint8 array
		int i;
		int k = 0;
		int strbuffer[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		for(i = 0; i<strlen(argv[2]); i++){
			// Check for escape char
			if(argv[2][i]==ESCAPE_CHAR){
				i++;
				char escstring[3] = {argv[2][i],0,0};
				strbuffer[k] = atoi(escstring);
			}
			// Otherwise copy over to buffer
			else
				strbuffer[k] = argv[2][i];
			k++;
		}
	
		// Tell AVR to listen up
		nBytes = usb_control_msg(handle, 
			USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 
			BEGIN_TRANSMIT, 0, 0, (char *)buffer, sizeof(buffer), 5000);
		
		// Send chars
		for(i = 0; i<16; i++){
			nBytes = usb_control_msg(handle, 
				USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 
				SEND_CHAR, strbuffer[i], 0, (char *)buffer, sizeof(buffer), 5000);
			//sleep(SLEEP_TIME); 
		}
		
		// End transmission and post to line
		nBytes = usb_control_msg(handle, 
			USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 
			atoi(argv[1]), 0, 0, (char *)buffer, sizeof(buffer), 5000);
	}

	if(nBytes < 0)
		fprintf(stderr, "USB error: %s\n", usb_strerror());
		
	usb_close(handle);
	
	return 0;
}
