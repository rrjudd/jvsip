#ifndef _vsipprivate_h
#define _vsipprivate_h 1

#define vsip_valid_structure_object (0x5555)
#define VSIP_VALID_STRUCTURE_OBJECT (0x5555)
#define vsip_freed_structure_object (0xAAAA)
#define VSIP_FREED_STRUCTURE_OBJECT (0xAAAA)
#define VSIP_RELEASED_BLOCK (0)
#define VSIP_ADMITTED_BLOCK (1)
#define VSIP_VSIPL_BLOCK    (0)
#define VSIP_USER_BLOCK     (1)
#define VSIP_DERIVED_BLOCK  (2)

struct vsip_cblock_f;
struct vsip_cblock_d;
struct vsip_blockattributes_f {
  vsip_cblock_f*   parent;     /* if derived point to parent                             */
  vsip_scalar_f*   array;      /* external data array                                    */
  int              kind;       /* 0 ==> private, 1 ==> public, 2==> derived              */
  int              admit;      /* 0 ==> No,      1 ==> Yes                               */
  vsip_stride      rstride;    /* real block stride; stride = view_stride * block_stride */
  size_t           size;       /* block size in elements                                 */
  int              bindings;   /* reference counter                                      */
  int              markings;   /* valid|destoyed block object                            */
  vsip_memory_hint hint;       /* Not used in this implementation                        */
  vsip_scalar_bl update;          /* a place to store update flag */
  };

struct vsip_blockattributes_d {
  vsip_cblock_d*   parent;        /* if derived point to parent else null                   */
  vsip_scalar_d*   array;         /* external data array                                    */
  int              kind;          /* 0 ==> private, 1 ==> public, 2==> derived              */
  int              admit;         /* 0 ==> No,      1 ==> Yes                               */
  vsip_stride      rstride;       /* real block stride; stride = view_stride * block_stride */
  size_t           size;          /* block size in elements                                 */
  int              bindings;      /* reference counter                                      */
  int              markings;      /* valid|destoyed block object                            */
  vsip_memory_hint hint;          /* Not used in this implementation                        */
  vsip_scalar_bl update;          /* a place to store update flag */
  };

struct vsip_cblockattributes_d {
  vsip_block_d *R,
               *I;            /* blocks holding data array                */
  int           kind;         /* 0 ==> private, 1 ==> public              */
  int           admit;        /* 0 ==> No,      1 ==> Yes                 */
  vsip_stride   cstride;      /* 1 for split, 2 for interleaved           */
  size_t        size;         /* block size in elements                   */
  int           bindings;     /* reference counter                        */
  int           markings;     /* valid|destoyed block object              */
  vsip_memory_hint hint;       /* not used in this implementation */
  vsip_cscalar_d a_scalar;
  vsip_cscalar_d a_zero;
  vsip_cscalar_d a_one;
  vsip_cscalar_d a_imag_one;
  vsip_scalar_bl update;          /* a place to store update flag */
  };

struct vsip_cblockattributes_f {
  vsip_block_f *R,
               *I;            /* blocks holding data arrays      */
  int           kind;         /* 0 ==> private, 1 ==> public     */
  int           admit;        /* 0 ==> No,      1 ==> Yes        */
  vsip_stride   cstride;      /* 1 for split, 2 for interleaved  */
  size_t        size;         /* block size in elements          */
  int           bindings;     /* reference counter               */
  int           markings;     /* valid|destoyed block object     */
  vsip_memory_hint hint;       /* not used in this implementation */
  vsip_cscalar_f a_scalar;
  vsip_cscalar_f a_zero;
  vsip_cscalar_f a_one;
  vsip_cscalar_f a_imag_one;
  vsip_scalar_bl update;          /* a place to store update flag */
};

struct vsip_blockattributes_i {
  vsip_scalar_i*   array;       /* external data array         */
  int              kind;        /* 0 ==> private, 1 ==> public */
  int              admit;       /* 0 ==> No,      1 ==> Yes    */
  size_t           size;        /* block size in elements      */
  int              bindings;    /* reference counter           */
  int              markings;    /* valid|destoyed block object */
  vsip_memory_hint hint;        /* Not used in this implementation */
  vsip_scalar_bl update;          /* a place to store update flag */
  };

struct vsip_blockattributes_vi {
  vsip_scalar_vi*  array;       /* external data array              */
  int              kind;        /* 0 ==> private, 1 ==> public      */
  int              admit;       /* 0 ==> No,      1 ==> Yes         */
  size_t           size;        /* block size in elements           */
  int              bindings;    /* reference counter                */
  int              markings;    /* valid|destoyed block object      */
  vsip_memory_hint hint;        /* not used in this implementation  */
  vsip_scalar_bl update;          /* a place to store update flag */
  };
#endif /* _vsipprivate_h */

