
#ifndef __DEMOS_H__
#define __DEMOS_H__

    /* Data structure */
    typedef struct {
      const char    *name;
      const uint16_t sector_number;
    } demos_structure_t;

    /* Regulator Map */
    demos_structure_t demos_map[] = {
      // Name      | Sector Number
      { "user"     ,          0*0},
      { "hello"    ,          1*2},
      { "dhry"     ,          2*2}
    };


#endif
