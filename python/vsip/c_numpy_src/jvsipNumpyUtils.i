 %module jvsipNumpyUtils
 %{
 /* Put header files here or function declarations like below */
#include "../../../c_VSIP_src/vsip.h"
#include "numpyArrayCopies.h"
 %}
typedef enum { VSIP_ROW = 0, VSIP_COL = 1 } vsip_major;
void vcopyToNParray_d(vsip_vview_d *, PyObject* );
void vcopyToNParray_f(vsip_vview_f *, PyObject* );
void cvcopyToNParray_d(vsip_cvview_d *, PyObject* );
void cvcopyToNParray_f(vsip_cvview_f *, PyObject* );
void mcopyToNParray_d(vsip_mview_d *, vsip_major, PyObject* );
void mcopyToNParray_f(vsip_mview_f *, vsip_major, PyObject* );
void cmcopyToNParray_d(vsip_cmview_d *, vsip_major, PyObject* );
void cmcopyToNParray_f(vsip_cmview_f *, vsip_major, PyObject* );
void vcopyFromNParray_d(vsip_vview_d *, PyObject* );
void vcopyFromNParray_f(vsip_vview_f *, PyObject* );
void cvcopyFromNParray_d(vsip_cvview_d *, PyObject* );
void cvcopyFromNParray_f(vsip_cvview_f *, PyObject* );
void mcopyFromNParray_d(vsip_mview_d *, vsip_major, PyObject* );
void mcopyFromNParray_f(vsip_mview_f *, vsip_major, PyObject* );
void cmcopyFromNParray_d(vsip_cmview_d *, vsip_major, PyObject* );
void cmcopyFromNParray_f(vsip_cmview_f *, vsip_major, PyObject* );
