#define XSTR(s) STR(s)
#define STR(s) #s

#ifndef PARM_NODE_TYPE
#error "You must define PARM_NODE_TYPE macro before include this file"
#endif

#ifndef PARM_FILEPATH_H
#define PARM_FILEPATH_H sd/node/##PARM_NODE_TYPE##.h
#endif

#include XSTR(PARM_FILEPATH_H)

#undef PARM_NODE_NAME
#undef PARM_NODE_TYPE
#undef PARM_FILEPATH_H
