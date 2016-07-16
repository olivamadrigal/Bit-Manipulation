//  Wrapper Functions:
//  Malloc/Realloc/Calloc/Fopen/Fclose
//

#ifndef sami_h
#define sami_h

void *Malloc(size_t size);
void *Realloc(void *ptr, size_t numMembers);
void *Calloc(size_t numMembers, size_t size);
FILE *Fopen(char *file, char *mode);
void  Fclose(FILE *fp);


#endif


