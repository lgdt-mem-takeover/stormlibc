/* sglgl.h
 *
 * Minimal custom OpenGL loader header for the subset used by your renderer.
 * Designed for SDL3 + OpenGL 3.3 core usage on Windows/Linux.
 *
 * Usage:
 *
 *   #define SGL_GL_IMPL
 *   #include "sglgl.h"
 *
 * in exactly one .c file.
 *
 * In other files:
 *
 *   #include "sglgl.h"
 *
 * After SDL_GL_CreateContext + SDL_GL_MakeCurrent:
 *
 *   if (!sgl_gl_load_all()) { ... fail ... }
 */

#ifndef SGL_GL_H
#define SGL_GL_H

// #include <stddef.h>   /* ptrdiff_t */
// #include <stdint.h>   /* standard integer types */
// #include <SDL3/SDL.h>
// #include <SDL3/SDL_video.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------ */
/* Calling convention                                            */
/* ------------------------------------------------------------ */

#ifndef APIENTRY
#  if defined(_WIN32) || defined(__CYGWIN__)
#    define APIENTRY __stdcall
#  else
#    define APIENTRY
#  endif
#endif

#ifndef APIENTRYP
#  define APIENTRYP APIENTRY *
#endif

/* ------------------------------------------------------------ */
/* GL scalar types                                               */
/* ------------------------------------------------------------ */

typedef unsigned int        GLenum;
typedef unsigned char       GLboolean;
typedef unsigned int        GLbitfield;
typedef void                GLvoid;
typedef signed char         GLbyte;
typedef short               GLshort;
typedef int                 GLint;
typedef int                 GLsizei;
typedef unsigned char       GLubyte;
typedef unsigned int        GLuint;
typedef float               GLfloat;
typedef char                GLchar;
typedef ptrdiff_t           GLintptr;
typedef ptrdiff_t           GLsizeiptr;

/* ------------------------------------------------------------ */
/* GL enum/constants actually used by your code                  */
/* Values match Khronos OpenGL headers.                          */
/* ------------------------------------------------------------ */

#define GL_FALSE                          0
#define GL_TRUE                           1

#define GL_FLOAT                          0x1406
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_UNSIGNED_INT                   0x1405

#define GL_TEXTURE_2D                     0x0DE1
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_LINEAR_MIPMAP_LINEAR           0x2703
#define GL_UNPACK_ALIGNMENT               0x0CF5

#define GL_RED                            0x1903
#define GL_RGBA                           0x1908
#define GL_R8                             0x8229
#define GL_RGBA8                          0x8058

#define GL_VERTEX_SHADER                  0x8B31
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_INFO_LOG_LENGTH                0x8B84

#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_BUFFER_SIZE                    0x8764
#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8

#define GL_SCISSOR_TEST 0x0C11

#define GL_TRIANGLES                      0x0004

#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_DEPTH_TEST                     0x0B71
#define GL_BLEND                          0x0BE2
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303

/* optional but useful soon */
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03

/* ------------------------------------------------------------ */
/* X-macro list                                                  */
/* ------------------------------------------------------------ */

#define SGL_GL_FUNCTIONS(X) \
X(GLint,  glGetUniformLocation,      (GLuint program, const GLchar *name)) \
X(void,	  glScissor,		     (GLint x, GLint y, GLsizei width, GLsizei height))\
X(void,   glViewport,                (GLint x, GLint y, GLsizei width, GLsizei height)) \
X(void,   glClearColor,              (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)) \
X(void,   glClear,                   (GLbitfield mask)) \
X(void,   glDisable,                 (GLenum cap)) \
X(void,   glEnable,                  (GLenum cap)) \
X(void,   glBlendFunc,               (GLenum sfactor, GLenum dfactor)) \
\
X(void,   glGenTextures,             (GLsizei n, GLuint *textures)) \
X(void,   glBindTexture,             (GLenum target, GLuint texture)) \
X(void,   glPixelStorei,             (GLenum pname, GLint param)) \
X(void,   glTexImage2D,              (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)) \
X(void,   glTexParameteri,           (GLenum target, GLenum pname, GLint param)) \
X(void,   glGenerateMipmap,          (GLenum target)) \
X(void,   glDeleteTextures,          (GLsizei n, const GLuint *textures)) \
X(void,   glActiveTexture,           (GLenum texture)) \
\
X(GLuint, glCreateShader,            (GLenum type)) \
X(void,   glShaderSource,            (GLuint shader, GLsizei count, const GLchar * const *string, const GLint *length)) \
X(void,   glCompileShader,           (GLuint shader)) \
X(void,   glGetShaderiv,             (GLuint shader, GLenum pname, GLint *params)) \
X(void,   glGetShaderInfoLog,        (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)) \
X(void,   glDeleteShader,            (GLuint shader)) \
\
X(GLuint, glCreateProgram,           (void)) \
X(void,   glAttachShader,            (GLuint program, GLuint shader)) \
X(void,   glLinkProgram,             (GLuint program)) \
X(void,   glGetProgramiv,            (GLuint program, GLenum pname, GLint *params)) \
X(void,   glGetProgramInfoLog,       (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)) \
X(void,   glDeleteProgram,           (GLuint program)) \
X(void,   glUseProgram,              (GLuint program)) \
\
X(void,   glGenVertexArrays,         (GLsizei n, GLuint *arrays)) \
X(void,   glBindVertexArray,         (GLuint array)) \
X(void,   glDeleteVertexArrays,      (GLsizei n, const GLuint *arrays)) \
\
X(void,   glGenBuffers,              (GLsizei n, GLuint *buffers)) \
X(void,   glBindBuffer,              (GLenum target, GLuint buffer)) \
X(void,   glBufferData,              (GLenum target, GLsizeiptr size, const void *data, GLenum usage)) \
X(void,   glBufferSubData,           (GLenum target, GLintptr offset, GLsizeiptr size, const void *data)) \
X(void,   glGetBufferParameteriv,    (GLenum target, GLenum pname, GLint *params)) \
X(void,   glDeleteBuffers,           (GLsizei n, const GLuint *buffers)) \
\
X(void,   glVertexAttribPointer,     (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)) \
X(void,   glEnableVertexAttribArray, (GLuint index)) \
\
X(void,   glUniform1f,               (GLint location, GLfloat v0)) \
X(void,   glUniform1i,               (GLint location, GLint v0)) \
X(void,   glUniform2f,               (GLint location, GLfloat v0, GLfloat v1)) \
\
X(void,   glDrawArrays,              (GLenum mode, GLint first, GLsizei count)) \
X(void,   glDrawElements,            (GLenum mode, GLsizei count, GLenum type, const void *indices)) \
\
X(const GLubyte *, glGetString,      (GLenum name)) \
X(void,   glGetIntegerv,             (GLenum pname, GLint *data)) \
X(GLenum, glGetError,                (void)) \
X(void,   glUniformMatrix4fv,        (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)) \
X(void,   glUniform3f,               (GLint location, GLfloat v0, GLfloat v1, GLfloat v2)) \
X(void,   glUniform4f,               (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3))

/* ------------------------------------------------------------ */
/* Typedefs + extern declarations                                */
/* ------------------------------------------------------------ */

#define SGL_GL_DECLARE_TYPE(ret, name, args) \
    typedef ret (APIENTRYP PFN##name##PROC) args;
SGL_GL_FUNCTIONS(SGL_GL_DECLARE_TYPE)
#undef SGL_GL_DECLARE_TYPE

#define SGL_GL_DECLARE_EXTERN(ret, name, args) \
    extern PFN##name##PROC name;
SGL_GL_FUNCTIONS(SGL_GL_DECLARE_EXTERN)
#undef SGL_GL_DECLARE_EXTERN

/* ------------------------------------------------------------ */
/* Loader helpers                                                */
/* ------------------------------------------------------------ */

int sgl_gl_load_all(void);
void *sgl_gl_get_proc_or_null(const char *name);

#ifdef SGL_GL_IMPL

#define SGL_GL_DEFINE_STORAGE(ret, name, args) \
    PFN##name##PROC name = NULL;
SGL_GL_FUNCTIONS(SGL_GL_DEFINE_STORAGE)
#undef SGL_GL_DEFINE_STORAGE

static int
sgl_gl__load_one_(const char *proc_name, void **out_fp)
{
    SDL_FunctionPointer fp = SDL_GL_GetProcAddress(proc_name);
    *out_fp = (void *) fp;
    return (*out_fp != NULL);
}

void *
sgl_gl_get_proc_or_null(const char *name)
{
    SDL_FunctionPointer fp = SDL_GL_GetProcAddress(name);
    return (void *) fp;
}

int
sgl_gl_load_all(void)
{
    int ok = 1;

#define SGL_GL_LOAD_ONE(ret, name, args) \
    do { \
        if (!sgl_gl__load_one_(#name, (void **) &name)) { \
            ok = 0; \
        } \
    } while (0);

    SGL_GL_FUNCTIONS(SGL_GL_LOAD_ONE)

#undef SGL_GL_LOAD_ONE
    return ok;
}

#endif /* SGL_GL_IMPL */

#ifdef __cplusplus
}
#endif

#endif /* SGL_GL_H */

