#ifndef NIMROD_FIELD_H
#define NIMROD_FIELD_H

#include "fusion_io_field.h"
#include "nimrod_source.h"
#include "options.h"

#ifdef __cplusplus
extern "C" {
#endif
void nimrod_fio_get_time(const double, int*)
#ifdef __cplusplus
}
#endif

class nimrod_fio_field : public fio_field {
 public:
  int get_real_parameter(const field_parameter, double*);
};

class nimrod_scalar_field : public nimrod_fio_field {
 protected:
  field_attribute species = 0;
 public:
  int dimension() const { return 1; }
  int load(const fio_option_list*);
};

class nimrod_vector_field : public nimrod_fio_field {
 public:
  int dimension() const { return 3; }
};

class nimrod_density_field : public nimrod_scalar_field {
 public:
  virtual int eval(const double*, double*, void* = nullptr);
};	

class nimrod_temperature_field : public nimrod_scalar_field {
 public:
  virtual int eval(const double*, double*, void* = nullptr);
};

class nimrod_magnetic_field : public nimrod_vector_field {
 public:
  virtual int eval(const double*, double*, void* = nullptr);
  virtual int eval_deriv(const double*, double*, void* = nullptr);
};

class nimrod_electric_field : public nimrod_vector_field {
 public:
  virtual int eval(const double*, double*, void* = nullptr);
  virtual int eval_deriv(const double*, double*, void* = nullptr);
};

#endif // NIMROD_FIELD_H