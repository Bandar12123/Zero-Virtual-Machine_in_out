ZVM — IN Instruction

Description

The IN instruction reads data from an IO device (such as the keyboard) and pushes the result onto the stack. It is the counterpart to the existing OUT instruction.


Signature

cIN(p, port, function, argc)

ParameterDescriptionpThe program (vm->program)portRegister holding the device port number (e.g. ZVM_IO_PORT_KEYBOARD)functionRegister holding the operation code requested from the deviceargcRegister holding the number of values expected back from the device


Usage Example

cLDI(VMP, R0, ZVM_IO_PORT_KEYBOARD)
LDI(VMP, R1, ZVM_IO_SERVICE_KEYBOARD_READ_CHARACTER)
LDI(VMP, R2, 1)        /* expected return values = 1 */

IN(VMP, R0, R1, R2)

POP(VMP, R3)            /* the character read is now in R3 */


How It Works


Validates that port is within bounds (< ZVM_IO_MAX_DEVICES)
Validates that the device exists (io_devices[port] != NULL)
Validates that the device type supports reading (ZVM_IO_DEVICE_TYPE_IN or ZVM_IO_DEVICE_TYPE_INOUT)
Calls the device's processor(), which fills its O[] buffer with results
Pushes the values from O[] onto the stack in reverse order, so the first result ends up on top of the stack



Possible Exceptions

ConditionExceptionport >= ZVM_IO_MAX_DEVICESBAD_INSTRUCTIONDevice not foundIO_DEVICE_NOT_FOUNDStack full while pushing resultsSTACK_OVERFLOW


IN vs OUT

INOUTDirectionDevice → ProgramProgram → DeviceSourcedevice->O[]Stack (pop)DestinationStack (push)device->I[]Required device typeIN or INOUTOUT or INOUT


Affected Files


zvm_instruction.h — added ZVM_OPCODE_IN, the function declaration, an entry in the handler table, and the IN(p, v1, v2, v3) macro
zvm_instruction.c — added the zfnx_in function
zvm_io.c — updated zfnio_keyboard to actually read from stdin via getchar()
