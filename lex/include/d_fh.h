#ifndef D_FH_H
#define D_FH_H

void init_stat();
void append_name_to_file(const char *filename, const char *datatype);
char* get_name_from_file(const char *filename, int n);
char* get_datatype_from_stat(int n);

#endif 