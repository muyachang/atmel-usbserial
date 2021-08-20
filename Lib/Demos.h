
#ifndef __DEMOS_H__
#define __DEMOS_H__

    /* Data structure */
    typedef struct {
      const char    *name;
      const uint16_t page_number;
    } demos_structure_t;

    /* Regulator Map */
    demos_structure_t demos_map[] = {
      // Name      | Page Number
      { "user"     ,        256*0},
      { "hello"    ,        256*1},
      { "dhry"     ,        256*2}
    };


#endif
