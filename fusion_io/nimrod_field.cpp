#include "fusion_io.h"

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

int nimrod_scalar_field::load(const fio_option_list* opt)
{
  int ierr = opt->get_option(FIO_SPECIES, &species);

  return (ierr == FIO_SUCCESS) ? FIO_SUCCESS : FIO_BAD_SPECIES;
}

int nimrod_density_field::eval(const double* x, double* v, void* s)
{
  int ierr = -1;
  if(s) {
    nimrod_fio_ndens_eval_hint(species, x, v,
                               static_cast<nimrod_search_hint*>(s), ierr);
  } else {
    nimrod_fio_ndens_eval(species, x, v, ierr);
  }
  return ierr;
}

int nimrod_temperature_field::eval(const double* x, double* v, void* s)
{
  int ierr = -1;
  if(s) {
    nimrod_fio_temp_eval_hint(species, x, v,
                               static_cast<nimrod_search_hint*>(s), ierr);
  } else {
    nimrod_fio_temp_eval(species, x, v, ierr);
  }
  return ierr;
}

int nimrod_magnetic_field::eval(const double* x, double* v, void* s)
{
  int ierr = -1;
  if(s) {
    nimrod_fio_b_eval_hint(x, v, static_cast<nimrod_search_hint*>(s), ierr);
  } else {
    nimrod_fio_b_eval(x, v, ierr);
  }
  return ierr;
}

int nimrod_magnetic_field::eval_deriv(const double* x, double* v, void* s)
{
  int ierr = -1;
  if(s) {
    nimrod_fio_b_eval_deriv_hint(x, v, static_cast<nimrod_search_hint*>(s),
      ierr);
  } else {
    nimrod_fio_b_eval_deriv(x, v, ierr);
  }
  return ierr;
}

int nimrod_electric_field::eval(const double* x, double* v, void* s)
{
  int ierr = -1;
  if(s) {
    nimrod_fio_e_eval_hint(x, v, static_cast<nimrod_search_hint*>(s), ierr);
  } else {
    nimrod_fio_e_eval(x, v, ierr);
  }
  return ierr;
}

int nimrod_electric_field::eval_deriv(const double* x, double* v, void* s)
{
  int ierr = -1;
  if(s) {
    nimrod_fio_e_eval_deriv_hint(x, v, static_cast<nimrod_search_hint*>(s),
      ierr);
  } else {
    nimrod_fio_e_eval_deriv(x, v, ierr);
  }
  return ierr;
}
