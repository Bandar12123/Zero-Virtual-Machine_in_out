#include "zvm.h"
#include "zvm_io.h"

bool zfnio_keyboard(zvm_vm_t *vm,  uint8_t port, uint8_t operation,  uint8_t argc){
    /* functions:
       0: read one character
    */
    (void)argc;

    if(operation == ZVM_IO_SERVICE_KEYBOARD_READ_CHARACTER){
        int c = getchar();
        if(c == EOF) c = 0;
        vm->io_devices[port]->O[0] = (uint8_t)c;
    }

    return true;
}

bool zfnio_screen(zvm_vm_t *vm, uint8_t port, uint8_t operation,  uint8_t argc){
    
    /* functions:
      0: write one character
    */
    (void)argc;
    (void)operation;

    uint8_t character = vm->io_devices[port]->I[0];
    printf("%c", character);
    return true;
}
