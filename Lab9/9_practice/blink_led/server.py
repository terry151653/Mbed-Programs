# You can write copyrights rules here. These rules will be copied into the outputs.

#
# Generated by erpcgen 1.9.0 on Sun Apr 17 23:11:30 2022.
#
# AUTOGENERATED - DO NOT EDIT
#

import erpc
from . import common, interface

# Client for LEDBlinkService
class LEDBlinkServiceService(erpc.server.Service):
    def __init__(self, handler):
        super(LEDBlinkServiceService, self).__init__(interface.ILEDBlinkService.SERVICE_ID)
        self._handler = handler
        self._methods = {
                interface.ILEDBlinkService.LED3_CHANGE_ID: self._handle_led3_change,
            }

    def _handle_led3_change(self, sequence, codec):
        # Read incoming parameters.

        # Invoke user implementation of remote function.
        self._handler.led3_change()

        # Prepare codec for reply message.
        codec.reset()

        # Construct reply message.
        codec.start_write_message(erpc.codec.MessageInfo(
            type=erpc.codec.MessageType.kReplyMessage,
            service=interface.ILEDBlinkService.SERVICE_ID,
            request=interface.ILEDBlinkService.LED3_CHANGE_ID,
            sequence=sequence))


