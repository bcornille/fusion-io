#include "nimrod_source.h"

int nimrod_source::open(const char* filename)
{
  int len_filename;
  if(!nimrod_fio_init_(filename, len_filename))
    return FIO_FILE_ERROR;

  return FIO_SUCCESS;
}

int nimrod_source::close()
{
  return FIO_SUCCESS;
}

int nimrod_source::get_available_fields(fio_field_list* fields) const
{
  fields->clear();
  fields->push_back(FIO_DENSITY);
  fields->push_back(FIO_TEMPERATURE);
  fields->push_back(FIO_MAGNETIC_FIELD);
  fields->push_back(FIO_ELECTRIC_FIELD);

  return FIO_SUCCESS;
}

int nimrod_source::get_field_options(fio_option_list* opt) const
{
  opt->clear();
  opt->add_option(FIO_SPECIES, 0);

  return FIO_SUCCESS;
}

int nimrod_source::get_field(const field_type t, fio_field** f,
                             const fio_option_list* opt)
{
  return FIO_UNSUPPORTED;
}

int nimrod_source::allocate_search_hint(void** s)
{
  *s = new nimrod_search_hint;
  return FIO_SUCCESS;
}

int nimrod_source::deallocate_search_hint(void** s)
{
  delete (nimrod_search_hint*)(*s);
  return FIO_SUCCESS;
}
