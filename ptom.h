#ifndef PTOM_H
#define PTOM_H

#ifdef __cplusplus
extern "C" {
#endif

int ptom_init(void);
int ptom_parse(char* mpath, char* ppath);
void ptom_deinit(void);
float ptom_getVersion(void);

#ifdef __cplusplus
}
#endif

#endif // PTOM_H