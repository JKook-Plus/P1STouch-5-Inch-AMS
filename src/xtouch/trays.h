
#include <stdint.h>

char tray_types[5][16];

char* get_tray_type(uint8_t tray_id){
    return tray_types[tray_id+1];
}
void set_tray_type(uint8_t tray_id, char* tray_type){
    strcpy(tray_types[tray_id+1],tray_type);
}