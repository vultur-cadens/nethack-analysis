#ifndef ATTR_H
#define ATTR_H

enum attrib_types {
    A_STR = 0,
    A_INT,
    A_WIS,
    A_DEX,
    A_CON,
    A_CHA,

    A_MAX
};

void
init_attr(unsigned char result[A_MAX],
          const unsigned char attrbase[A_MAX],
          const unsigned char attrdist[A_MAX],
          const unsigned char attrmax[A_MAX],
          const unsigned char attrmin[A_MAX],
          int np);

void
vary_init_attr(unsigned char result[A_MAX],
               const unsigned char attrmax[A_MAX],
               const unsigned char attrmin[A_MAX]);

#endif /* ATTR_H */
