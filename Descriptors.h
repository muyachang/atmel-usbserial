/** \file
 *
 *  Header file for Descriptors.c.
 */
 
#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

  /* Includes: */
    #include <avr/pgmspace.h>

    #include <LUFA/Drivers/USB/USB.h>
    #include <LUFA/Drivers/USB/Class/CDC.h>

  /* Macros: */
    /** Endpoint number of the CDC device-to-host notification IN endpoint. */
    #define CDC_NOTIFICATION_EPNUM         2

    /** Endpoint number of the CDC device-to-host data IN endpoint. */
    #define CDC_TX_EPNUM                   3  

    /** Endpoint number of the CDC host-to-device data OUT endpoint. */
    #define CDC_RX_EPNUM                   4  

    /** Size in bytes of the CDC device-to-host notification IN endpoint. */
    #define CDC_NOTIFICATION_EPSIZE        8

    /** Size in bytes of the CDC data IN and OUT endpoints. */
    #define CDC_TXRX_EPSIZE                64  

  /* Type Defines: */
    /** Type define for the device configuration descriptor structure. This must be defined in the
     *  application code, as the configuration descriptor contains several sub-descriptors which
     *  vary between devices, and which describe the device's usage to the host.
     */
    typedef struct
    {
      USB_Descriptor_Configuration_Header_t    Config;
      USB_Descriptor_Interface_t               CDC_CCI_Interface;
      CDC_FUNCTIONAL_DESCRIPTOR(2)             CDC_Functional_IntHeader;
      CDC_FUNCTIONAL_DESCRIPTOR(1)             CDC_Functional_AbstractControlManagement;
      CDC_FUNCTIONAL_DESCRIPTOR(2)             CDC_Functional_Union;
      USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;
      USB_Descriptor_Interface_t               CDC_DCI_Interface;
      USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
      USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
    } USB_Descriptor_Configuration_t;

  /* Function Prototypes: */
    uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                        const uint8_t wIndex,
                                        const void** const DescriptorAddress) ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
