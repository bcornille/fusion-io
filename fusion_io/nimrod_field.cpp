#include "nimrod_field.h"

int nimrod_fio_field::get_real_parameter(const field_parameter t, double *p)
{
  int ierr = -1;
	switch(t) {
  case FIO_TIME:
    nimrod_fio_get_time(t, &ierr);
    return ierr;

  default:
    return FIO_UNSUPPORTED;
  }
}