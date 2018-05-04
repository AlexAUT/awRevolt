#include <aw/opengl/impl/gl_core_3_3.hpp>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#if defined(__APPLE__)
#include <dlfcn.h>

static void* AppleGLGetProcAddress(const char* name)
{
  static void* image = NULL;

  if (NULL == image)
    image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);

  return (image ? dlsym(image, name) : NULL);
}
#endif /* __APPLE__ */

#if defined(__sgi) || defined(__sun)
#include <dlfcn.h>
#include <stdio.h>

static void* SunGetProcAddress(const GLubyte* name)
{
  static void* h = NULL;
  static void* gpa;

  if (h == NULL)
  {
    if ((h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL)) == NULL)
      return NULL;
    gpa = dlsym(h, "glXGetProcAddress");
  }

  if (gpa != NULL)
    return ((void* (*)(const GLubyte*))gpa)(name);
  else
    return dlsym(h, (const char*)name);
}
#endif /* __sgi || __sun */

#if defined(_WIN32)

#ifdef _MSC_VER
#pragma warning(disable : 4055)
#pragma warning(disable : 4054)
#pragma warning(disable : 4996)
#endif

static int TestPointer(const PROC pTest)
{
  ptrdiff_t iTest;
  if (!pTest)
    return 0;
  iTest = (ptrdiff_t)pTest;

  if (iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1)
    return 0;

  return 1;
}

static PROC WinGetProcAddress(const char* name)
{
  HMODULE glMod = NULL;
  PROC pFunc = wglGetProcAddress((LPCSTR)name);
  if (TestPointer(pFunc))
  {
    return pFunc;
  }
  glMod = GetModuleHandleA("OpenGL32.dll");
  return (PROC)GetProcAddress(glMod, (LPCSTR)name);
}

#define IntGetProcAddress(name) WinGetProcAddress(name)
#else
#if defined(__APPLE__)
#define IntGetProcAddress(name) AppleGLGetProcAddress(name)
#else
#if defined(__sgi) || defined(__sun)
#define IntGetProcAddress(name) SunGetProcAddress(name)
#else /* GLX */
#include <GL/glx.h>

#define IntGetProcAddress(name) (*glXGetProcAddressARB)((const GLubyte*)name)
#endif
#endif
#endif

void(CODEGEN_FUNCPTR* _ptrc_glAccum)(GLenum op, GLfloat value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glAlphaFunc)(GLenum func, GLfloat ref) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBegin)(GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBitmap)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove,
                                      GLfloat ymove, const GLubyte* bitmap) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBlendFunc)(GLenum sfactor, GLenum dfactor) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCallList)(GLuint list) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCallLists)(GLsizei n, GLenum type, const void* lists) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClear)(GLbitfield mask) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClearAccum)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClearDepth)(GLdouble depth) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClearIndex)(GLfloat c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClearStencil)(GLint s) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClipPlane)(GLenum plane, const GLdouble* equation) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3b)(GLbyte red, GLbyte green, GLbyte blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3bv)(const GLbyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3d)(GLdouble red, GLdouble green, GLdouble blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3f)(GLfloat red, GLfloat green, GLfloat blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3i)(GLint red, GLint green, GLint blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3s)(GLshort red, GLshort green, GLshort blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3ub)(GLubyte red, GLubyte green, GLubyte blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3ubv)(const GLubyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3ui)(GLuint red, GLuint green, GLuint blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3uiv)(const GLuint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3us)(GLushort red, GLushort green, GLushort blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor3usv)(const GLushort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4b)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4bv)(const GLbyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4d)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4f)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4i)(GLint red, GLint green, GLint blue, GLint alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4s)(GLshort red, GLshort green, GLshort blue, GLshort alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4ub)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4ubv)(const GLubyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4ui)(GLuint red, GLuint green, GLuint blue, GLuint alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4uiv)(const GLuint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4us)(GLushort red, GLushort green, GLushort blue, GLushort alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColor4usv)(const GLushort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColorMaterial)(GLenum face, GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCopyPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCullFace)(GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDeleteLists)(GLuint list, GLsizei range) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDepthFunc)(GLenum func) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDepthMask)(GLboolean flag) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDepthRange)(GLdouble ren_near, GLdouble ren_far) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDisable)(GLenum cap) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDrawBuffer)(GLenum buf) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDrawPixels)(GLsizei width, GLsizei height, GLenum format, GLenum type,
                                          const void* pixels) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEdgeFlag)(GLboolean flag) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEdgeFlagv)(const GLboolean* flag) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEnable)(GLenum cap) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEnd)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEndList)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalCoord1d)(GLdouble u) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalCoord1dv)(const GLdouble* u) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalCoord1f)(GLfloat u) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalCoord1fv)(const GLfloat* u) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalCoord2d)(GLdouble u, GLdouble v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalCoord2dv)(const GLdouble* u) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalCoord2f)(GLfloat u, GLfloat v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalCoord2fv)(const GLfloat* u) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalMesh1)(GLenum mode, GLint i1, GLint i2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalMesh2)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalPoint1)(GLint i) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEvalPoint2)(GLint i, GLint j) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFeedbackBuffer)(GLsizei size, GLenum type, GLfloat* buffer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFinish)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFlush)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFogf)(GLenum pname, GLfloat param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFogfv)(GLenum pname, const GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFogi)(GLenum pname, GLint param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFogiv)(GLenum pname, const GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFrontFace)(GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFrustum)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear,
                                       GLdouble zFar) = NULL;
GLuint(CODEGEN_FUNCPTR* _ptrc_glGenLists)(GLsizei range) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetBooleanv)(GLenum pname, GLboolean* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetClipPlane)(GLenum plane, GLdouble* equation) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetDoublev)(GLenum pname, GLdouble* data) = NULL;
GLenum(CODEGEN_FUNCPTR* _ptrc_glGetError)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetFloatv)(GLenum pname, GLfloat* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetIntegerv)(GLenum pname, GLint* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetLightfv)(GLenum light, GLenum pname, GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetLightiv)(GLenum light, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetMapdv)(GLenum target, GLenum query, GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetMapfv)(GLenum target, GLenum query, GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetMapiv)(GLenum target, GLenum query, GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetMaterialfv)(GLenum face, GLenum pname, GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetMaterialiv)(GLenum face, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetPixelMapfv)(GLenum map, GLfloat* values) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetPixelMapuiv)(GLenum map, GLuint* values) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetPixelMapusv)(GLenum map, GLushort* values) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetPolygonStipple)(GLubyte* mask) = NULL;
const GLubyte*(CODEGEN_FUNCPTR* _ptrc_glGetString)(GLenum name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexEnvfv)(GLenum target, GLenum pname, GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexEnviv)(GLenum target, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexGendv)(GLenum coord, GLenum pname, GLdouble* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexGenfv)(GLenum coord, GLenum pname, GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexGeniv)(GLenum coord, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexImage)(GLenum target, GLint level, GLenum format, GLenum type, void* pixels) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexLevelParameterfv)(GLenum target, GLint level, GLenum pname, GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexLevelParameteriv)(GLenum target, GLint level, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexParameterfv)(GLenum target, GLenum pname, GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexParameteriv)(GLenum target, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glHint)(GLenum target, GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexMask)(GLuint mask) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexd)(GLdouble c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexdv)(const GLdouble* c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexf)(GLfloat c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexfv)(const GLfloat* c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexi)(GLint c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexiv)(const GLint* c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexs)(GLshort c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexsv)(const GLshort* c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glInitNames)(void) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsEnabled)(GLenum cap) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsList)(GLuint list) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLightModelf)(GLenum pname, GLfloat param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLightModelfv)(GLenum pname, const GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLightModeli)(GLenum pname, GLint param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLightModeliv)(GLenum pname, const GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLightf)(GLenum light, GLenum pname, GLfloat param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLightfv)(GLenum light, GLenum pname, const GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLighti)(GLenum light, GLenum pname, GLint param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLightiv)(GLenum light, GLenum pname, const GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLineStipple)(GLint factor, GLushort pattern) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLineWidth)(GLfloat width) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glListBase)(GLuint base) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLoadIdentity)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLoadMatrixd)(const GLdouble* m) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLoadMatrixf)(const GLfloat* m) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLoadName)(GLuint name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLogicOp)(GLenum opcode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMap1d)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order,
                                     const GLdouble* points) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMap1f)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order,
                                     const GLfloat* points) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMap2d)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1,
                                     GLdouble v2, GLint vstride, GLint vorder, const GLdouble* points) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMap2f)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1,
                                     GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMapGrid1d)(GLint un, GLdouble u1, GLdouble u2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMapGrid1f)(GLint un, GLfloat u1, GLfloat u2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMapGrid2d)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMapGrid2f)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMaterialf)(GLenum face, GLenum pname, GLfloat param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMaterialfv)(GLenum face, GLenum pname, const GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMateriali)(GLenum face, GLenum pname, GLint param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMaterialiv)(GLenum face, GLenum pname, const GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMatrixMode)(GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultMatrixd)(const GLdouble* m) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultMatrixf)(const GLfloat* m) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNewList)(GLuint list, GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormal3b)(GLbyte nx, GLbyte ny, GLbyte nz) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormal3bv)(const GLbyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormal3d)(GLdouble nx, GLdouble ny, GLdouble nz) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormal3dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormal3f)(GLfloat nx, GLfloat ny, GLfloat nz) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormal3fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormal3i)(GLint nx, GLint ny, GLint nz) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormal3iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormal3s)(GLshort nx, GLshort ny, GLshort nz) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormal3sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glOrtho)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear,
                                     GLdouble zFar) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPassThrough)(GLfloat token) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPixelMapfv)(GLenum map, GLsizei mapsize, const GLfloat* values) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPixelMapuiv)(GLenum map, GLsizei mapsize, const GLuint* values) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPixelMapusv)(GLenum map, GLsizei mapsize, const GLushort* values) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPixelStoref)(GLenum pname, GLfloat param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPixelStorei)(GLenum pname, GLint param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPixelTransferf)(GLenum pname, GLfloat param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPixelTransferi)(GLenum pname, GLint param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPixelZoom)(GLfloat xfactor, GLfloat yfactor) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPointSize)(GLfloat size) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPolygonMode)(GLenum face, GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPolygonStipple)(const GLubyte* mask) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPopAttrib)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPopMatrix)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPopName)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPushAttrib)(GLbitfield mask) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPushMatrix)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPushName)(GLuint name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos2d)(GLdouble x, GLdouble y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos2dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos2f)(GLfloat x, GLfloat y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos2fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos2i)(GLint x, GLint y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos2iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos2s)(GLshort x, GLshort y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos2sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos3d)(GLdouble x, GLdouble y, GLdouble z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos3dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos3f)(GLfloat x, GLfloat y, GLfloat z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos3fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos3i)(GLint x, GLint y, GLint z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos3iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos3s)(GLshort x, GLshort y, GLshort z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos3sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos4dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos4fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos4i)(GLint x, GLint y, GLint z, GLint w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos4iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos4s)(GLshort x, GLshort y, GLshort z, GLshort w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRasterPos4sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glReadBuffer)(GLenum src) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type,
                                          void* pixels) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRectd)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRectdv)(const GLdouble* v1, const GLdouble* v2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRectf)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRectfv)(const GLfloat* v1, const GLfloat* v2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRecti)(GLint x1, GLint y1, GLint x2, GLint y2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRectiv)(const GLint* v1, const GLint* v2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRects)(GLshort x1, GLshort y1, GLshort x2, GLshort y2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRectsv)(const GLshort* v1, const GLshort* v2) = NULL;
GLint(CODEGEN_FUNCPTR* _ptrc_glRenderMode)(GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRotated)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRotatef)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glScaled)(GLdouble x, GLdouble y, GLdouble z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glScalef)(GLfloat x, GLfloat y, GLfloat z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glScissor)(GLint x, GLint y, GLsizei width, GLsizei height) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSelectBuffer)(GLsizei size, GLuint* buffer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glShadeModel)(GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glStencilFunc)(GLenum func, GLint ref, GLuint mask) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glStencilMask)(GLuint mask) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glStencilOp)(GLenum fail, GLenum zfail, GLenum zpass) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord1d)(GLdouble s) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord1dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord1f)(GLfloat s) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord1fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord1i)(GLint s) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord1iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord1s)(GLshort s) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord1sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord2d)(GLdouble s, GLdouble t) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord2dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord2f)(GLfloat s, GLfloat t) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord2fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord2i)(GLint s, GLint t) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord2iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord2s)(GLshort s, GLshort t) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord2sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord3d)(GLdouble s, GLdouble t, GLdouble r) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord3dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord3f)(GLfloat s, GLfloat t, GLfloat r) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord3fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord3i)(GLint s, GLint t, GLint r) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord3iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord3s)(GLshort s, GLshort t, GLshort r) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord3sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord4d)(GLdouble s, GLdouble t, GLdouble r, GLdouble q) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord4dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord4f)(GLfloat s, GLfloat t, GLfloat r, GLfloat q) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord4fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord4i)(GLint s, GLint t, GLint r, GLint q) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord4iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord4s)(GLshort s, GLshort t, GLshort r, GLshort q) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoord4sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexEnvf)(GLenum target, GLenum pname, GLfloat param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexEnvfv)(GLenum target, GLenum pname, const GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexEnvi)(GLenum target, GLenum pname, GLint param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexEnviv)(GLenum target, GLenum pname, const GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexGend)(GLenum coord, GLenum pname, GLdouble param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexGendv)(GLenum coord, GLenum pname, const GLdouble* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexGenf)(GLenum coord, GLenum pname, GLfloat param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexGenfv)(GLenum coord, GLenum pname, const GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexGeni)(GLenum coord, GLenum pname, GLint param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexGeniv)(GLenum coord, GLenum pname, const GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexImage1D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border,
                                          GLenum format, GLenum type, const void* pixels) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width,
                                          GLsizei height, GLint border, GLenum format, GLenum type,
                                          const void* pixels) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexParameterf)(GLenum target, GLenum pname, GLfloat param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexParameterfv)(GLenum target, GLenum pname, const GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexParameteri)(GLenum target, GLenum pname, GLint param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexParameteriv)(GLenum target, GLenum pname, const GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTranslated)(GLdouble x, GLdouble y, GLdouble z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTranslatef)(GLfloat x, GLfloat y, GLfloat z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex2d)(GLdouble x, GLdouble y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex2dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex2f)(GLfloat x, GLfloat y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex2fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex2i)(GLint x, GLint y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex2iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex2s)(GLshort x, GLshort y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex2sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex3d)(GLdouble x, GLdouble y, GLdouble z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex3dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex3f)(GLfloat x, GLfloat y, GLfloat z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex3fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex3i)(GLint x, GLint y, GLint z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex3iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex3s)(GLshort x, GLshort y, GLshort z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex3sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex4dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex4fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex4i)(GLint x, GLint y, GLint z, GLint w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex4iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex4s)(GLshort x, GLshort y, GLshort z, GLshort w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertex4sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glViewport)(GLint x, GLint y, GLsizei width, GLsizei height) = NULL;

GLboolean(CODEGEN_FUNCPTR* _ptrc_glAreTexturesResident)(GLsizei n, const GLuint* textures,
                                                        GLboolean* residences) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glArrayElement)(GLint i) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBindTexture)(GLenum target, GLuint texture) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColorPointer)(GLint size, GLenum type, GLsizei stride, const void* pointer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCopyTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y,
                                              GLsizei width, GLint border) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y,
                                              GLsizei width, GLsizei height, GLint border) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCopyTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y,
                                                 GLsizei width) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x,
                                                 GLint y, GLsizei width, GLsizei height) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDeleteTextures)(GLsizei n, const GLuint* textures) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDisableClientState)(GLenum ren_array) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDrawArrays)(GLenum mode, GLint first, GLsizei count) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void* indices) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEdgeFlagPointer)(GLsizei stride, const void* pointer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEnableClientState)(GLenum ren_array) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGenTextures)(GLsizei n, GLuint* textures) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetPointerv)(GLenum pname, void** params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexPointer)(GLenum type, GLsizei stride, const void* pointer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexub)(GLubyte c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glIndexubv)(const GLubyte* c) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glInterleavedArrays)(GLenum format, GLsizei stride, const void* pointer) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsTexture)(GLuint texture) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glNormalPointer)(GLenum type, GLsizei stride, const void* pointer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPolygonOffset)(GLfloat factor, GLfloat units) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPopClientAttrib)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPrioritizeTextures)(GLsizei n, const GLuint* textures, const GLfloat* priorities) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPushClientAttrib)(GLbitfield mask) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexCoordPointer)(GLint size, GLenum type, GLsizei stride, const void* pointer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format,
                                             GLenum type, const void* pixels) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
                                             GLsizei height, GLenum format, GLenum type, const void* pixels) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexPointer)(GLint size, GLenum type, GLsizei stride, const void* pointer) = NULL;

void(CODEGEN_FUNCPTR* _ptrc_glCopyTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                                                 GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type,
                                                 const void* indices) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width,
                                          GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type,
                                          const void* pixels) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
                                             GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type,
                                             const void* pixels) = NULL;

void(CODEGEN_FUNCPTR* _ptrc_glActiveTexture)(GLenum texture) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClientActiveTexture)(GLenum texture) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCompressedTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLsizei width,
                                                    GLint border, GLsizei imageSize, const void* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width,
                                                    GLsizei height, GLint border, GLsizei imageSize,
                                                    const void* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCompressedTexImage3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width,
                                                    GLsizei height, GLsizei depth, GLint border, GLsizei imageSize,
                                                    const void* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCompressedTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width,
                                                       GLenum format, GLsizei imageSize, const void* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                                                       GLsizei width, GLsizei height, GLenum format, GLsizei imageSize,
                                                       const void* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCompressedTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                                                       GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
                                                       GLenum format, GLsizei imageSize, const void* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetCompressedTexImage)(GLenum target, GLint level, void* img) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLoadTransposeMatrixd)(const GLdouble* m) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLoadTransposeMatrixf)(const GLfloat* m) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultTransposeMatrixd)(const GLdouble* m) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultTransposeMatrixf)(const GLfloat* m) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord1d)(GLenum target, GLdouble s) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord1dv)(GLenum target, const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord1f)(GLenum target, GLfloat s) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord1fv)(GLenum target, const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord1i)(GLenum target, GLint s) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord1iv)(GLenum target, const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord1s)(GLenum target, GLshort s) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord1sv)(GLenum target, const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord2d)(GLenum target, GLdouble s, GLdouble t) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord2dv)(GLenum target, const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord2f)(GLenum target, GLfloat s, GLfloat t) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord2fv)(GLenum target, const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord2i)(GLenum target, GLint s, GLint t) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord2iv)(GLenum target, const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord2s)(GLenum target, GLshort s, GLshort t) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord2sv)(GLenum target, const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord3d)(GLenum target, GLdouble s, GLdouble t, GLdouble r) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord3dv)(GLenum target, const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord3f)(GLenum target, GLfloat s, GLfloat t, GLfloat r) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord3fv)(GLenum target, const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord3i)(GLenum target, GLint s, GLint t, GLint r) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord3iv)(GLenum target, const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord3s)(GLenum target, GLshort s, GLshort t, GLshort r) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord3sv)(GLenum target, const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord4d)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord4dv)(GLenum target, const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord4f)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord4fv)(GLenum target, const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord4i)(GLenum target, GLint s, GLint t, GLint r, GLint q) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord4iv)(GLenum target, const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord4s)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiTexCoord4sv)(GLenum target, const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSampleCoverage)(GLfloat value, GLboolean invert) = NULL;

void(CODEGEN_FUNCPTR* _ptrc_glBlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBlendEquation)(GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha,
                                                 GLenum dfactorAlpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFogCoordPointer)(GLenum type, GLsizei stride, const void* pointer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFogCoordd)(GLdouble coord) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFogCoorddv)(const GLdouble* coord) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFogCoordf)(GLfloat coord) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFogCoordfv)(const GLfloat* coord) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiDrawArrays)(GLenum mode, const GLint* first, const GLsizei* count,
                                               GLsizei drawcount) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glMultiDrawElements)(GLenum mode, const GLsizei* count, GLenum type,
                                                 const void* const* indices, GLsizei drawcount) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPointParameterf)(GLenum pname, GLfloat param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPointParameterfv)(GLenum pname, const GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPointParameteri)(GLenum pname, GLint param) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glPointParameteriv)(GLenum pname, const GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3b)(GLbyte red, GLbyte green, GLbyte blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3bv)(const GLbyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3d)(GLdouble red, GLdouble green, GLdouble blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3f)(GLfloat red, GLfloat green, GLfloat blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3i)(GLint red, GLint green, GLint blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3s)(GLshort red, GLshort green, GLshort blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3ub)(GLubyte red, GLubyte green, GLubyte blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3ubv)(const GLubyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3ui)(GLuint red, GLuint green, GLuint blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3uiv)(const GLuint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3us)(GLushort red, GLushort green, GLushort blue) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColor3usv)(const GLushort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glSecondaryColorPointer)(GLint size, GLenum type, GLsizei stride,
                                                     const void* pointer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos2d)(GLdouble x, GLdouble y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos2dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos2f)(GLfloat x, GLfloat y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos2fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos2i)(GLint x, GLint y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos2iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos2s)(GLshort x, GLshort y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos2sv)(const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos3d)(GLdouble x, GLdouble y, GLdouble z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos3dv)(const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos3f)(GLfloat x, GLfloat y, GLfloat z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos3fv)(const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos3i)(GLint x, GLint y, GLint z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos3iv)(const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos3s)(GLshort x, GLshort y, GLshort z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glWindowPos3sv)(const GLshort* v) = NULL;

void(CODEGEN_FUNCPTR* _ptrc_glBeginQuery)(GLenum target, GLuint id) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBindBuffer)(GLenum target, GLuint buffer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBufferData)(GLenum target, GLsizeiptr size, const void* data, GLenum usage) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDeleteBuffers)(GLsizei n, const GLuint* buffers) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDeleteQueries)(GLsizei n, const GLuint* ids) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEndQuery)(GLenum target) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGenBuffers)(GLsizei n, GLuint* buffers) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGenQueries)(GLsizei n, GLuint* ids) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetBufferParameteriv)(GLenum target, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetBufferPointerv)(GLenum target, GLenum pname, void** params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, void* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetQueryObjectiv)(GLuint id, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetQueryObjectuiv)(GLuint id, GLenum pname, GLuint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetQueryiv)(GLenum target, GLenum pname, GLint* params) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsBuffer)(GLuint buffer) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsQuery)(GLuint id) = NULL;
void*(CODEGEN_FUNCPTR* _ptrc_glMapBuffer)(GLenum target, GLenum access) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glUnmapBuffer)(GLenum target) = NULL;

void(CODEGEN_FUNCPTR* _ptrc_glAttachShader)(GLuint program, GLuint shader) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBindAttribLocation)(GLuint program, GLuint index, const GLchar* name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glCompileShader)(GLuint shader) = NULL;
GLuint(CODEGEN_FUNCPTR* _ptrc_glCreateProgram)(void) = NULL;
GLuint(CODEGEN_FUNCPTR* _ptrc_glCreateShader)(GLenum type) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDeleteProgram)(GLuint program) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDeleteShader)(GLuint shader) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDetachShader)(GLuint program, GLuint shader) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDisableVertexAttribArray)(GLuint index) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDrawBuffers)(GLsizei n, const GLenum* bufs) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEnableVertexAttribArray)(GLuint index) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length,
                                               GLint* size, GLenum* type, GLchar* name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length,
                                                GLint* size, GLenum* type, GLchar* name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei* count,
                                                  GLuint* shaders) = NULL;
GLint(CODEGEN_FUNCPTR* _ptrc_glGetAttribLocation)(GLuint program, const GLchar* name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei* length,
                                                 GLchar* infoLog) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetProgramiv)(GLuint program, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei* length,
                                                GLchar* infoLog) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetShaderiv)(GLuint shader, GLenum pname, GLint* params) = NULL;
GLint(CODEGEN_FUNCPTR* _ptrc_glGetUniformLocation)(GLuint program, const GLchar* name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetUniformfv)(GLuint program, GLint location, GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetUniformiv)(GLuint program, GLint location, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetVertexAttribPointerv)(GLuint index, GLenum pname, void** pointer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetVertexAttribdv)(GLuint index, GLenum pname, GLdouble* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetVertexAttribfv)(GLuint index, GLenum pname, GLfloat* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetVertexAttribiv)(GLuint index, GLenum pname, GLint* params) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsProgram)(GLuint program) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsShader)(GLuint shader) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glLinkProgram)(GLuint program) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glShaderSource)(GLuint shader, GLsizei count, const GLchar* const* string,
                                            const GLint* length) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glStencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glStencilMaskSeparate)(GLenum face, GLuint mask) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glStencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform1f)(GLint location, GLfloat v0) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform1fv)(GLint location, GLsizei count, const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform1i)(GLint location, GLint v0) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform1iv)(GLint location, GLsizei count, const GLint* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform2f)(GLint location, GLfloat v0, GLfloat v1) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform2fv)(GLint location, GLsizei count, const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform2i)(GLint location, GLint v0, GLint v1) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform2iv)(GLint location, GLsizei count, const GLint* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform3fv)(GLint location, GLsizei count, const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform3i)(GLint location, GLint v0, GLint v1, GLint v2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform3iv)(GLint location, GLsizei count, const GLint* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform4fv)(GLint location, GLsizei count, const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform4iv)(GLint location, GLsizei count, const GLint* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose,
                                                const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose,
                                                const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose,
                                                const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUseProgram)(GLuint program) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glValidateProgram)(GLuint program) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib1d)(GLuint index, GLdouble x) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib1dv)(GLuint index, const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib1f)(GLuint index, GLfloat x) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib1fv)(GLuint index, const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib1s)(GLuint index, GLshort x) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib1sv)(GLuint index, const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib2d)(GLuint index, GLdouble x, GLdouble y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib2dv)(GLuint index, const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib2f)(GLuint index, GLfloat x, GLfloat y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib2fv)(GLuint index, const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib2s)(GLuint index, GLshort x, GLshort y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib2sv)(GLuint index, const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib3d)(GLuint index, GLdouble x, GLdouble y, GLdouble z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib3dv)(GLuint index, const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib3fv)(GLuint index, const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib3s)(GLuint index, GLshort x, GLshort y, GLshort z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib3sv)(GLuint index, const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4Nbv)(GLuint index, const GLbyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4Niv)(GLuint index, const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4Nsv)(GLuint index, const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4Nub)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4Nubv)(GLuint index, const GLubyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4Nuiv)(GLuint index, const GLuint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4Nusv)(GLuint index, const GLushort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4bv)(GLuint index, const GLbyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4d)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4dv)(GLuint index, const GLdouble* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4fv)(GLuint index, const GLfloat* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4iv)(GLuint index, const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4s)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4sv)(GLuint index, const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4ubv)(GLuint index, const GLubyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4uiv)(GLuint index, const GLuint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttrib4usv)(GLuint index, const GLushort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                                   GLsizei stride, const void* pointer) = NULL;

void(CODEGEN_FUNCPTR* _ptrc_glUniformMatrix2x3fv)(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniformMatrix2x4fv)(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniformMatrix3x2fv)(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniformMatrix3x4fv)(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniformMatrix4x2fv)(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniformMatrix4x3fv)(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat* value) = NULL;

void(CODEGEN_FUNCPTR* _ptrc_glBeginConditionalRender)(GLuint id, GLenum mode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBeginTransformFeedback)(GLenum primitiveMode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBindBufferBase)(GLenum target, GLuint index, GLuint buffer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBindBufferRange)(GLenum target, GLuint index, GLuint buffer, GLintptr offset,
                                               GLsizeiptr size) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBindFragDataLocation)(GLuint program, GLuint color, const GLchar* name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBindFramebuffer)(GLenum target, GLuint framebuffer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBindRenderbuffer)(GLenum target, GLuint renderbuffer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBindVertexArray)(GLuint ren_array) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glBlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0,
                                               GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask,
                                               GLenum filter) = NULL;
GLenum(CODEGEN_FUNCPTR* _ptrc_glCheckFramebufferStatus)(GLenum target) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClampColor)(GLenum target, GLenum clamp) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClearBufferfi)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClearBufferfv)(GLenum buffer, GLint drawbuffer, const GLfloat* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClearBufferiv)(GLenum buffer, GLint drawbuffer, const GLint* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glClearBufferuiv)(GLenum buffer, GLint drawbuffer, const GLuint* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glColorMaski)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDeleteFramebuffers)(GLsizei n, const GLuint* framebuffers) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDeleteRenderbuffers)(GLsizei n, const GLuint* renderbuffers) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDeleteVertexArrays)(GLsizei n, const GLuint* arrays) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glDisablei)(GLenum target, GLuint index) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEnablei)(GLenum target, GLuint index) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEndConditionalRender)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glEndTransformFeedback)(void) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFlushMappedBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget,
                                                       GLuint renderbuffer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFramebufferTexture1D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture,
                                                    GLint level) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture,
                                                    GLint level) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFramebufferTexture3D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture,
                                                    GLint level, GLint zoffset) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glFramebufferTextureLayer)(GLenum target, GLenum attachment, GLuint texture, GLint level,
                                                       GLint layer) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGenFramebuffers)(GLsizei n, GLuint* framebuffers) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGenRenderbuffers)(GLsizei n, GLuint* renderbuffers) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGenVertexArrays)(GLsizei n, GLuint* arrays) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGenerateMipmap)(GLenum target) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetBooleani_v)(GLenum target, GLuint index, GLboolean* data) = NULL;
GLint(CODEGEN_FUNCPTR* _ptrc_glGetFragDataLocation)(GLuint program, const GLchar* name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname,
                                                                   GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetIntegeri_v)(GLenum target, GLuint index, GLint* data) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint* params) = NULL;
const GLubyte*(CODEGEN_FUNCPTR* _ptrc_glGetStringi)(GLenum name, GLuint index) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexParameterIiv)(GLenum target, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTexParameterIuiv)(GLenum target, GLenum pname, GLuint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetTransformFeedbackVarying)(GLuint program, GLuint index, GLsizei bufSize,
                                                           GLsizei* length, GLsizei* size, GLenum* type,
                                                           GLchar* name) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetUniformuiv)(GLuint program, GLint location, GLuint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetVertexAttribIiv)(GLuint index, GLenum pname, GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glGetVertexAttribIuiv)(GLuint index, GLenum pname, GLuint* params) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsEnabledi)(GLenum target, GLuint index) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsFramebuffer)(GLuint framebuffer) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsRenderbuffer)(GLuint renderbuffer) = NULL;
GLboolean(CODEGEN_FUNCPTR* _ptrc_glIsVertexArray)(GLuint ren_array) = NULL;
void*(CODEGEN_FUNCPTR* _ptrc_glMapBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length,
                                               GLbitfield access) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width,
                                                   GLsizei height) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glRenderbufferStorageMultisample)(GLenum target, GLsizei samples, GLenum internalformat,
                                                              GLsizei width, GLsizei height) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexParameterIiv)(GLenum target, GLenum pname, const GLint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTexParameterIuiv)(GLenum target, GLenum pname, const GLuint* params) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glTransformFeedbackVaryings)(GLuint program, GLsizei count, const GLchar* const* varyings,
                                                         GLenum bufferMode) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform1ui)(GLint location, GLuint v0) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform1uiv)(GLint location, GLsizei count, const GLuint* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform2ui)(GLint location, GLuint v0, GLuint v1) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform2uiv)(GLint location, GLsizei count, const GLuint* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform3ui)(GLint location, GLuint v0, GLuint v1, GLuint v2) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform3uiv)(GLint location, GLsizei count, const GLuint* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform4ui)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glUniform4uiv)(GLint location, GLsizei count, const GLuint* value) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI1i)(GLuint index, GLint x) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI1iv)(GLuint index, const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI1ui)(GLuint index, GLuint x) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI1uiv)(GLuint index, const GLuint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI2i)(GLuint index, GLint x, GLint y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI2iv)(GLuint index, const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI2ui)(GLuint index, GLuint x, GLuint y) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI2uiv)(GLuint index, const GLuint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI3i)(GLuint index, GLint x, GLint y, GLint z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI3iv)(GLuint index, const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI3ui)(GLuint index, GLuint x, GLuint y, GLuint z) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI3uiv)(GLuint index, const GLuint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI4bv)(GLuint index, const GLbyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI4i)(GLuint index, GLint x, GLint y, GLint z, GLint w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI4iv)(GLuint index, const GLint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI4sv)(GLuint index, const GLshort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI4ubv)(GLuint index, const GLubyte* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI4ui)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI4uiv)(GLuint index, const GLuint* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribI4usv)(GLuint index, const GLushort* v) = NULL;
void(CODEGEN_FUNCPTR* _ptrc_glVertexAttribIPointer)(GLuint index, GLint size, GLenum type, GLsizei stride,
                                                    const void* pointer) = NULL;

static int Load_Version_3_0(void)
{
  int numFailed = 0;
  _ptrc_glAccum = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat))IntGetProcAddress("glAccum");
  if (!_ptrc_glAccum)
    numFailed++;
  _ptrc_glAlphaFunc = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat))IntGetProcAddress("glAlphaFunc");
  if (!_ptrc_glAlphaFunc)
    numFailed++;
  _ptrc_glBegin = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glBegin");
  if (!_ptrc_glBegin)
    numFailed++;
  _ptrc_glBitmap = (void(CODEGEN_FUNCPTR*)(GLsizei, GLsizei, GLfloat, GLfloat, GLfloat, GLfloat,
                                           const GLubyte*))IntGetProcAddress("glBitmap");
  if (!_ptrc_glBitmap)
    numFailed++;
  _ptrc_glBlendFunc = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum))IntGetProcAddress("glBlendFunc");
  if (!_ptrc_glBlendFunc)
    numFailed++;
  _ptrc_glCallList = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glCallList");
  if (!_ptrc_glCallList)
    numFailed++;
  _ptrc_glCallLists = (void(CODEGEN_FUNCPTR*)(GLsizei, GLenum, const void*))IntGetProcAddress("glCallLists");
  if (!_ptrc_glCallLists)
    numFailed++;
  _ptrc_glClear = (void(CODEGEN_FUNCPTR*)(GLbitfield))IntGetProcAddress("glClear");
  if (!_ptrc_glClear)
    numFailed++;
  _ptrc_glClearAccum = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glClearAccum");
  if (!_ptrc_glClearAccum)
    numFailed++;
  _ptrc_glClearColor = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glClearColor");
  if (!_ptrc_glClearColor)
    numFailed++;
  _ptrc_glClearDepth = (void(CODEGEN_FUNCPTR*)(GLdouble))IntGetProcAddress("glClearDepth");
  if (!_ptrc_glClearDepth)
    numFailed++;
  _ptrc_glClearIndex = (void(CODEGEN_FUNCPTR*)(GLfloat))IntGetProcAddress("glClearIndex");
  if (!_ptrc_glClearIndex)
    numFailed++;
  _ptrc_glClearStencil = (void(CODEGEN_FUNCPTR*)(GLint))IntGetProcAddress("glClearStencil");
  if (!_ptrc_glClearStencil)
    numFailed++;
  _ptrc_glClipPlane = (void(CODEGEN_FUNCPTR*)(GLenum, const GLdouble*))IntGetProcAddress("glClipPlane");
  if (!_ptrc_glClipPlane)
    numFailed++;
  _ptrc_glColor3b = (void(CODEGEN_FUNCPTR*)(GLbyte, GLbyte, GLbyte))IntGetProcAddress("glColor3b");
  if (!_ptrc_glColor3b)
    numFailed++;
  _ptrc_glColor3bv = (void(CODEGEN_FUNCPTR*)(const GLbyte*))IntGetProcAddress("glColor3bv");
  if (!_ptrc_glColor3bv)
    numFailed++;
  _ptrc_glColor3d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble))IntGetProcAddress("glColor3d");
  if (!_ptrc_glColor3d)
    numFailed++;
  _ptrc_glColor3dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glColor3dv");
  if (!_ptrc_glColor3dv)
    numFailed++;
  _ptrc_glColor3f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat))IntGetProcAddress("glColor3f");
  if (!_ptrc_glColor3f)
    numFailed++;
  _ptrc_glColor3fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glColor3fv");
  if (!_ptrc_glColor3fv)
    numFailed++;
  _ptrc_glColor3i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint))IntGetProcAddress("glColor3i");
  if (!_ptrc_glColor3i)
    numFailed++;
  _ptrc_glColor3iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glColor3iv");
  if (!_ptrc_glColor3iv)
    numFailed++;
  _ptrc_glColor3s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort))IntGetProcAddress("glColor3s");
  if (!_ptrc_glColor3s)
    numFailed++;
  _ptrc_glColor3sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glColor3sv");
  if (!_ptrc_glColor3sv)
    numFailed++;
  _ptrc_glColor3ub = (void(CODEGEN_FUNCPTR*)(GLubyte, GLubyte, GLubyte))IntGetProcAddress("glColor3ub");
  if (!_ptrc_glColor3ub)
    numFailed++;
  _ptrc_glColor3ubv = (void(CODEGEN_FUNCPTR*)(const GLubyte*))IntGetProcAddress("glColor3ubv");
  if (!_ptrc_glColor3ubv)
    numFailed++;
  _ptrc_glColor3ui = (void(CODEGEN_FUNCPTR*)(GLuint, GLuint, GLuint))IntGetProcAddress("glColor3ui");
  if (!_ptrc_glColor3ui)
    numFailed++;
  _ptrc_glColor3uiv = (void(CODEGEN_FUNCPTR*)(const GLuint*))IntGetProcAddress("glColor3uiv");
  if (!_ptrc_glColor3uiv)
    numFailed++;
  _ptrc_glColor3us = (void(CODEGEN_FUNCPTR*)(GLushort, GLushort, GLushort))IntGetProcAddress("glColor3us");
  if (!_ptrc_glColor3us)
    numFailed++;
  _ptrc_glColor3usv = (void(CODEGEN_FUNCPTR*)(const GLushort*))IntGetProcAddress("glColor3usv");
  if (!_ptrc_glColor3usv)
    numFailed++;
  _ptrc_glColor4b = (void(CODEGEN_FUNCPTR*)(GLbyte, GLbyte, GLbyte, GLbyte))IntGetProcAddress("glColor4b");
  if (!_ptrc_glColor4b)
    numFailed++;
  _ptrc_glColor4bv = (void(CODEGEN_FUNCPTR*)(const GLbyte*))IntGetProcAddress("glColor4bv");
  if (!_ptrc_glColor4bv)
    numFailed++;
  _ptrc_glColor4d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glColor4d");
  if (!_ptrc_glColor4d)
    numFailed++;
  _ptrc_glColor4dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glColor4dv");
  if (!_ptrc_glColor4dv)
    numFailed++;
  _ptrc_glColor4f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glColor4f");
  if (!_ptrc_glColor4f)
    numFailed++;
  _ptrc_glColor4fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glColor4fv");
  if (!_ptrc_glColor4fv)
    numFailed++;
  _ptrc_glColor4i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint, GLint))IntGetProcAddress("glColor4i");
  if (!_ptrc_glColor4i)
    numFailed++;
  _ptrc_glColor4iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glColor4iv");
  if (!_ptrc_glColor4iv)
    numFailed++;
  _ptrc_glColor4s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort, GLshort))IntGetProcAddress("glColor4s");
  if (!_ptrc_glColor4s)
    numFailed++;
  _ptrc_glColor4sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glColor4sv");
  if (!_ptrc_glColor4sv)
    numFailed++;
  _ptrc_glColor4ub = (void(CODEGEN_FUNCPTR*)(GLubyte, GLubyte, GLubyte, GLubyte))IntGetProcAddress("glColor4ub");
  if (!_ptrc_glColor4ub)
    numFailed++;
  _ptrc_glColor4ubv = (void(CODEGEN_FUNCPTR*)(const GLubyte*))IntGetProcAddress("glColor4ubv");
  if (!_ptrc_glColor4ubv)
    numFailed++;
  _ptrc_glColor4ui = (void(CODEGEN_FUNCPTR*)(GLuint, GLuint, GLuint, GLuint))IntGetProcAddress("glColor4ui");
  if (!_ptrc_glColor4ui)
    numFailed++;
  _ptrc_glColor4uiv = (void(CODEGEN_FUNCPTR*)(const GLuint*))IntGetProcAddress("glColor4uiv");
  if (!_ptrc_glColor4uiv)
    numFailed++;
  _ptrc_glColor4us = (void(CODEGEN_FUNCPTR*)(GLushort, GLushort, GLushort, GLushort))IntGetProcAddress("glColor4us");
  if (!_ptrc_glColor4us)
    numFailed++;
  _ptrc_glColor4usv = (void(CODEGEN_FUNCPTR*)(const GLushort*))IntGetProcAddress("glColor4usv");
  if (!_ptrc_glColor4usv)
    numFailed++;
  _ptrc_glColorMask =
      (void(CODEGEN_FUNCPTR*)(GLboolean, GLboolean, GLboolean, GLboolean))IntGetProcAddress("glColorMask");
  if (!_ptrc_glColorMask)
    numFailed++;
  _ptrc_glColorMaterial = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum))IntGetProcAddress("glColorMaterial");
  if (!_ptrc_glColorMaterial)
    numFailed++;
  _ptrc_glCopyPixels =
      (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLsizei, GLsizei, GLenum))IntGetProcAddress("glCopyPixels");
  if (!_ptrc_glCopyPixels)
    numFailed++;
  _ptrc_glCullFace = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glCullFace");
  if (!_ptrc_glCullFace)
    numFailed++;
  _ptrc_glDeleteLists = (void(CODEGEN_FUNCPTR*)(GLuint, GLsizei))IntGetProcAddress("glDeleteLists");
  if (!_ptrc_glDeleteLists)
    numFailed++;
  _ptrc_glDepthFunc = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glDepthFunc");
  if (!_ptrc_glDepthFunc)
    numFailed++;
  _ptrc_glDepthMask = (void(CODEGEN_FUNCPTR*)(GLboolean))IntGetProcAddress("glDepthMask");
  if (!_ptrc_glDepthMask)
    numFailed++;
  _ptrc_glDepthRange = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble))IntGetProcAddress("glDepthRange");
  if (!_ptrc_glDepthRange)
    numFailed++;
  _ptrc_glDisable = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glDisable");
  if (!_ptrc_glDisable)
    numFailed++;
  _ptrc_glDrawBuffer = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glDrawBuffer");
  if (!_ptrc_glDrawBuffer)
    numFailed++;
  _ptrc_glDrawPixels =
      (void(CODEGEN_FUNCPTR*)(GLsizei, GLsizei, GLenum, GLenum, const void*))IntGetProcAddress("glDrawPixels");
  if (!_ptrc_glDrawPixels)
    numFailed++;
  _ptrc_glEdgeFlag = (void(CODEGEN_FUNCPTR*)(GLboolean))IntGetProcAddress("glEdgeFlag");
  if (!_ptrc_glEdgeFlag)
    numFailed++;
  _ptrc_glEdgeFlagv = (void(CODEGEN_FUNCPTR*)(const GLboolean*))IntGetProcAddress("glEdgeFlagv");
  if (!_ptrc_glEdgeFlagv)
    numFailed++;
  _ptrc_glEnable = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glEnable");
  if (!_ptrc_glEnable)
    numFailed++;
  _ptrc_glEnd = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glEnd");
  if (!_ptrc_glEnd)
    numFailed++;
  _ptrc_glEndList = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glEndList");
  if (!_ptrc_glEndList)
    numFailed++;
  _ptrc_glEvalCoord1d = (void(CODEGEN_FUNCPTR*)(GLdouble))IntGetProcAddress("glEvalCoord1d");
  if (!_ptrc_glEvalCoord1d)
    numFailed++;
  _ptrc_glEvalCoord1dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glEvalCoord1dv");
  if (!_ptrc_glEvalCoord1dv)
    numFailed++;
  _ptrc_glEvalCoord1f = (void(CODEGEN_FUNCPTR*)(GLfloat))IntGetProcAddress("glEvalCoord1f");
  if (!_ptrc_glEvalCoord1f)
    numFailed++;
  _ptrc_glEvalCoord1fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glEvalCoord1fv");
  if (!_ptrc_glEvalCoord1fv)
    numFailed++;
  _ptrc_glEvalCoord2d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble))IntGetProcAddress("glEvalCoord2d");
  if (!_ptrc_glEvalCoord2d)
    numFailed++;
  _ptrc_glEvalCoord2dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glEvalCoord2dv");
  if (!_ptrc_glEvalCoord2dv)
    numFailed++;
  _ptrc_glEvalCoord2f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat))IntGetProcAddress("glEvalCoord2f");
  if (!_ptrc_glEvalCoord2f)
    numFailed++;
  _ptrc_glEvalCoord2fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glEvalCoord2fv");
  if (!_ptrc_glEvalCoord2fv)
    numFailed++;
  _ptrc_glEvalMesh1 = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint))IntGetProcAddress("glEvalMesh1");
  if (!_ptrc_glEvalMesh1)
    numFailed++;
  _ptrc_glEvalMesh2 = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLint, GLint))IntGetProcAddress("glEvalMesh2");
  if (!_ptrc_glEvalMesh2)
    numFailed++;
  _ptrc_glEvalPoint1 = (void(CODEGEN_FUNCPTR*)(GLint))IntGetProcAddress("glEvalPoint1");
  if (!_ptrc_glEvalPoint1)
    numFailed++;
  _ptrc_glEvalPoint2 = (void(CODEGEN_FUNCPTR*)(GLint, GLint))IntGetProcAddress("glEvalPoint2");
  if (!_ptrc_glEvalPoint2)
    numFailed++;
  _ptrc_glFeedbackBuffer = (void(CODEGEN_FUNCPTR*)(GLsizei, GLenum, GLfloat*))IntGetProcAddress("glFeedbackBuffer");
  if (!_ptrc_glFeedbackBuffer)
    numFailed++;
  _ptrc_glFinish = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glFinish");
  if (!_ptrc_glFinish)
    numFailed++;
  _ptrc_glFlush = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glFlush");
  if (!_ptrc_glFlush)
    numFailed++;
  _ptrc_glFogf = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat))IntGetProcAddress("glFogf");
  if (!_ptrc_glFogf)
    numFailed++;
  _ptrc_glFogfv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLfloat*))IntGetProcAddress("glFogfv");
  if (!_ptrc_glFogfv)
    numFailed++;
  _ptrc_glFogi = (void(CODEGEN_FUNCPTR*)(GLenum, GLint))IntGetProcAddress("glFogi");
  if (!_ptrc_glFogi)
    numFailed++;
  _ptrc_glFogiv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLint*))IntGetProcAddress("glFogiv");
  if (!_ptrc_glFogiv)
    numFailed++;
  _ptrc_glFrontFace = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glFrontFace");
  if (!_ptrc_glFrontFace)
    numFailed++;
  _ptrc_glFrustum = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble,
                                            GLdouble))IntGetProcAddress("glFrustum");
  if (!_ptrc_glFrustum)
    numFailed++;
  _ptrc_glGenLists = (GLuint(CODEGEN_FUNCPTR*)(GLsizei))IntGetProcAddress("glGenLists");
  if (!_ptrc_glGenLists)
    numFailed++;
  _ptrc_glGetBooleanv = (void(CODEGEN_FUNCPTR*)(GLenum, GLboolean*))IntGetProcAddress("glGetBooleanv");
  if (!_ptrc_glGetBooleanv)
    numFailed++;
  _ptrc_glGetClipPlane = (void(CODEGEN_FUNCPTR*)(GLenum, GLdouble*))IntGetProcAddress("glGetClipPlane");
  if (!_ptrc_glGetClipPlane)
    numFailed++;
  _ptrc_glGetDoublev = (void(CODEGEN_FUNCPTR*)(GLenum, GLdouble*))IntGetProcAddress("glGetDoublev");
  if (!_ptrc_glGetDoublev)
    numFailed++;
  _ptrc_glGetError = (GLenum(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glGetError");
  if (!_ptrc_glGetError)
    numFailed++;
  _ptrc_glGetFloatv = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat*))IntGetProcAddress("glGetFloatv");
  if (!_ptrc_glGetFloatv)
    numFailed++;
  _ptrc_glGetIntegerv = (void(CODEGEN_FUNCPTR*)(GLenum, GLint*))IntGetProcAddress("glGetIntegerv");
  if (!_ptrc_glGetIntegerv)
    numFailed++;
  _ptrc_glGetLightfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat*))IntGetProcAddress("glGetLightfv");
  if (!_ptrc_glGetLightfv)
    numFailed++;
  _ptrc_glGetLightiv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint*))IntGetProcAddress("glGetLightiv");
  if (!_ptrc_glGetLightiv)
    numFailed++;
  _ptrc_glGetMapdv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLdouble*))IntGetProcAddress("glGetMapdv");
  if (!_ptrc_glGetMapdv)
    numFailed++;
  _ptrc_glGetMapfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat*))IntGetProcAddress("glGetMapfv");
  if (!_ptrc_glGetMapfv)
    numFailed++;
  _ptrc_glGetMapiv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint*))IntGetProcAddress("glGetMapiv");
  if (!_ptrc_glGetMapiv)
    numFailed++;
  _ptrc_glGetMaterialfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat*))IntGetProcAddress("glGetMaterialfv");
  if (!_ptrc_glGetMaterialfv)
    numFailed++;
  _ptrc_glGetMaterialiv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint*))IntGetProcAddress("glGetMaterialiv");
  if (!_ptrc_glGetMaterialiv)
    numFailed++;
  _ptrc_glGetPixelMapfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat*))IntGetProcAddress("glGetPixelMapfv");
  if (!_ptrc_glGetPixelMapfv)
    numFailed++;
  _ptrc_glGetPixelMapuiv = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint*))IntGetProcAddress("glGetPixelMapuiv");
  if (!_ptrc_glGetPixelMapuiv)
    numFailed++;
  _ptrc_glGetPixelMapusv = (void(CODEGEN_FUNCPTR*)(GLenum, GLushort*))IntGetProcAddress("glGetPixelMapusv");
  if (!_ptrc_glGetPixelMapusv)
    numFailed++;
  _ptrc_glGetPolygonStipple = (void(CODEGEN_FUNCPTR*)(GLubyte*))IntGetProcAddress("glGetPolygonStipple");
  if (!_ptrc_glGetPolygonStipple)
    numFailed++;
  _ptrc_glGetString = (const GLubyte*(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glGetString");
  if (!_ptrc_glGetString)
    numFailed++;
  _ptrc_glGetTexEnvfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat*))IntGetProcAddress("glGetTexEnvfv");
  if (!_ptrc_glGetTexEnvfv)
    numFailed++;
  _ptrc_glGetTexEnviv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint*))IntGetProcAddress("glGetTexEnviv");
  if (!_ptrc_glGetTexEnviv)
    numFailed++;
  _ptrc_glGetTexGendv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLdouble*))IntGetProcAddress("glGetTexGendv");
  if (!_ptrc_glGetTexGendv)
    numFailed++;
  _ptrc_glGetTexGenfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat*))IntGetProcAddress("glGetTexGenfv");
  if (!_ptrc_glGetTexGenfv)
    numFailed++;
  _ptrc_glGetTexGeniv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint*))IntGetProcAddress("glGetTexGeniv");
  if (!_ptrc_glGetTexGeniv)
    numFailed++;
  _ptrc_glGetTexImage =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLenum, GLenum, void*))IntGetProcAddress("glGetTexImage");
  if (!_ptrc_glGetTexImage)
    numFailed++;
  _ptrc_glGetTexLevelParameterfv =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLenum, GLfloat*))IntGetProcAddress("glGetTexLevelParameterfv");
  if (!_ptrc_glGetTexLevelParameterfv)
    numFailed++;
  _ptrc_glGetTexLevelParameteriv =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLenum, GLint*))IntGetProcAddress("glGetTexLevelParameteriv");
  if (!_ptrc_glGetTexLevelParameteriv)
    numFailed++;
  _ptrc_glGetTexParameterfv =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat*))IntGetProcAddress("glGetTexParameterfv");
  if (!_ptrc_glGetTexParameterfv)
    numFailed++;
  _ptrc_glGetTexParameteriv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint*))IntGetProcAddress("glGetTexParameteriv");
  if (!_ptrc_glGetTexParameteriv)
    numFailed++;
  _ptrc_glHint = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum))IntGetProcAddress("glHint");
  if (!_ptrc_glHint)
    numFailed++;
  _ptrc_glIndexMask = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glIndexMask");
  if (!_ptrc_glIndexMask)
    numFailed++;
  _ptrc_glIndexd = (void(CODEGEN_FUNCPTR*)(GLdouble))IntGetProcAddress("glIndexd");
  if (!_ptrc_glIndexd)
    numFailed++;
  _ptrc_glIndexdv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glIndexdv");
  if (!_ptrc_glIndexdv)
    numFailed++;
  _ptrc_glIndexf = (void(CODEGEN_FUNCPTR*)(GLfloat))IntGetProcAddress("glIndexf");
  if (!_ptrc_glIndexf)
    numFailed++;
  _ptrc_glIndexfv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glIndexfv");
  if (!_ptrc_glIndexfv)
    numFailed++;
  _ptrc_glIndexi = (void(CODEGEN_FUNCPTR*)(GLint))IntGetProcAddress("glIndexi");
  if (!_ptrc_glIndexi)
    numFailed++;
  _ptrc_glIndexiv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glIndexiv");
  if (!_ptrc_glIndexiv)
    numFailed++;
  _ptrc_glIndexs = (void(CODEGEN_FUNCPTR*)(GLshort))IntGetProcAddress("glIndexs");
  if (!_ptrc_glIndexs)
    numFailed++;
  _ptrc_glIndexsv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glIndexsv");
  if (!_ptrc_glIndexsv)
    numFailed++;
  _ptrc_glInitNames = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glInitNames");
  if (!_ptrc_glInitNames)
    numFailed++;
  _ptrc_glIsEnabled = (GLboolean(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glIsEnabled");
  if (!_ptrc_glIsEnabled)
    numFailed++;
  _ptrc_glIsList = (GLboolean(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glIsList");
  if (!_ptrc_glIsList)
    numFailed++;
  _ptrc_glLightModelf = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat))IntGetProcAddress("glLightModelf");
  if (!_ptrc_glLightModelf)
    numFailed++;
  _ptrc_glLightModelfv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLfloat*))IntGetProcAddress("glLightModelfv");
  if (!_ptrc_glLightModelfv)
    numFailed++;
  _ptrc_glLightModeli = (void(CODEGEN_FUNCPTR*)(GLenum, GLint))IntGetProcAddress("glLightModeli");
  if (!_ptrc_glLightModeli)
    numFailed++;
  _ptrc_glLightModeliv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLint*))IntGetProcAddress("glLightModeliv");
  if (!_ptrc_glLightModeliv)
    numFailed++;
  _ptrc_glLightf = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat))IntGetProcAddress("glLightf");
  if (!_ptrc_glLightf)
    numFailed++;
  _ptrc_glLightfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLfloat*))IntGetProcAddress("glLightfv");
  if (!_ptrc_glLightfv)
    numFailed++;
  _ptrc_glLighti = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint))IntGetProcAddress("glLighti");
  if (!_ptrc_glLighti)
    numFailed++;
  _ptrc_glLightiv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLint*))IntGetProcAddress("glLightiv");
  if (!_ptrc_glLightiv)
    numFailed++;
  _ptrc_glLineStipple = (void(CODEGEN_FUNCPTR*)(GLint, GLushort))IntGetProcAddress("glLineStipple");
  if (!_ptrc_glLineStipple)
    numFailed++;
  _ptrc_glLineWidth = (void(CODEGEN_FUNCPTR*)(GLfloat))IntGetProcAddress("glLineWidth");
  if (!_ptrc_glLineWidth)
    numFailed++;
  _ptrc_glListBase = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glListBase");
  if (!_ptrc_glListBase)
    numFailed++;
  _ptrc_glLoadIdentity = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glLoadIdentity");
  if (!_ptrc_glLoadIdentity)
    numFailed++;
  _ptrc_glLoadMatrixd = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glLoadMatrixd");
  if (!_ptrc_glLoadMatrixd)
    numFailed++;
  _ptrc_glLoadMatrixf = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glLoadMatrixf");
  if (!_ptrc_glLoadMatrixf)
    numFailed++;
  _ptrc_glLoadName = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glLoadName");
  if (!_ptrc_glLoadName)
    numFailed++;
  _ptrc_glLogicOp = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glLogicOp");
  if (!_ptrc_glLogicOp)
    numFailed++;
  _ptrc_glMap1d =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLdouble, GLdouble, GLint, GLint, const GLdouble*))IntGetProcAddress("glMap1d");
  if (!_ptrc_glMap1d)
    numFailed++;
  _ptrc_glMap1f =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat, GLfloat, GLint, GLint, const GLfloat*))IntGetProcAddress("glMap1f");
  if (!_ptrc_glMap1f)
    numFailed++;
  _ptrc_glMap2d = (void(CODEGEN_FUNCPTR*)(GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint,
                                          const GLdouble*))IntGetProcAddress("glMap2d");
  if (!_ptrc_glMap2d)
    numFailed++;
  _ptrc_glMap2f = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint,
                                          const GLfloat*))IntGetProcAddress("glMap2f");
  if (!_ptrc_glMap2f)
    numFailed++;
  _ptrc_glMapGrid1d = (void(CODEGEN_FUNCPTR*)(GLint, GLdouble, GLdouble))IntGetProcAddress("glMapGrid1d");
  if (!_ptrc_glMapGrid1d)
    numFailed++;
  _ptrc_glMapGrid1f = (void(CODEGEN_FUNCPTR*)(GLint, GLfloat, GLfloat))IntGetProcAddress("glMapGrid1f");
  if (!_ptrc_glMapGrid1f)
    numFailed++;
  _ptrc_glMapGrid2d =
      (void(CODEGEN_FUNCPTR*)(GLint, GLdouble, GLdouble, GLint, GLdouble, GLdouble))IntGetProcAddress("glMapGrid2d");
  if (!_ptrc_glMapGrid2d)
    numFailed++;
  _ptrc_glMapGrid2f =
      (void(CODEGEN_FUNCPTR*)(GLint, GLfloat, GLfloat, GLint, GLfloat, GLfloat))IntGetProcAddress("glMapGrid2f");
  if (!_ptrc_glMapGrid2f)
    numFailed++;
  _ptrc_glMaterialf = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat))IntGetProcAddress("glMaterialf");
  if (!_ptrc_glMaterialf)
    numFailed++;
  _ptrc_glMaterialfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLfloat*))IntGetProcAddress("glMaterialfv");
  if (!_ptrc_glMaterialfv)
    numFailed++;
  _ptrc_glMateriali = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint))IntGetProcAddress("glMateriali");
  if (!_ptrc_glMateriali)
    numFailed++;
  _ptrc_glMaterialiv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLint*))IntGetProcAddress("glMaterialiv");
  if (!_ptrc_glMaterialiv)
    numFailed++;
  _ptrc_glMatrixMode = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glMatrixMode");
  if (!_ptrc_glMatrixMode)
    numFailed++;
  _ptrc_glMultMatrixd = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glMultMatrixd");
  if (!_ptrc_glMultMatrixd)
    numFailed++;
  _ptrc_glMultMatrixf = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glMultMatrixf");
  if (!_ptrc_glMultMatrixf)
    numFailed++;
  _ptrc_glNewList = (void(CODEGEN_FUNCPTR*)(GLuint, GLenum))IntGetProcAddress("glNewList");
  if (!_ptrc_glNewList)
    numFailed++;
  _ptrc_glNormal3b = (void(CODEGEN_FUNCPTR*)(GLbyte, GLbyte, GLbyte))IntGetProcAddress("glNormal3b");
  if (!_ptrc_glNormal3b)
    numFailed++;
  _ptrc_glNormal3bv = (void(CODEGEN_FUNCPTR*)(const GLbyte*))IntGetProcAddress("glNormal3bv");
  if (!_ptrc_glNormal3bv)
    numFailed++;
  _ptrc_glNormal3d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble))IntGetProcAddress("glNormal3d");
  if (!_ptrc_glNormal3d)
    numFailed++;
  _ptrc_glNormal3dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glNormal3dv");
  if (!_ptrc_glNormal3dv)
    numFailed++;
  _ptrc_glNormal3f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat))IntGetProcAddress("glNormal3f");
  if (!_ptrc_glNormal3f)
    numFailed++;
  _ptrc_glNormal3fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glNormal3fv");
  if (!_ptrc_glNormal3fv)
    numFailed++;
  _ptrc_glNormal3i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint))IntGetProcAddress("glNormal3i");
  if (!_ptrc_glNormal3i)
    numFailed++;
  _ptrc_glNormal3iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glNormal3iv");
  if (!_ptrc_glNormal3iv)
    numFailed++;
  _ptrc_glNormal3s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort))IntGetProcAddress("glNormal3s");
  if (!_ptrc_glNormal3s)
    numFailed++;
  _ptrc_glNormal3sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glNormal3sv");
  if (!_ptrc_glNormal3sv)
    numFailed++;
  _ptrc_glOrtho =
      (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glOrtho");
  if (!_ptrc_glOrtho)
    numFailed++;
  _ptrc_glPassThrough = (void(CODEGEN_FUNCPTR*)(GLfloat))IntGetProcAddress("glPassThrough");
  if (!_ptrc_glPassThrough)
    numFailed++;
  _ptrc_glPixelMapfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLsizei, const GLfloat*))IntGetProcAddress("glPixelMapfv");
  if (!_ptrc_glPixelMapfv)
    numFailed++;
  _ptrc_glPixelMapuiv = (void(CODEGEN_FUNCPTR*)(GLenum, GLsizei, const GLuint*))IntGetProcAddress("glPixelMapuiv");
  if (!_ptrc_glPixelMapuiv)
    numFailed++;
  _ptrc_glPixelMapusv = (void(CODEGEN_FUNCPTR*)(GLenum, GLsizei, const GLushort*))IntGetProcAddress("glPixelMapusv");
  if (!_ptrc_glPixelMapusv)
    numFailed++;
  _ptrc_glPixelStoref = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat))IntGetProcAddress("glPixelStoref");
  if (!_ptrc_glPixelStoref)
    numFailed++;
  _ptrc_glPixelStorei = (void(CODEGEN_FUNCPTR*)(GLenum, GLint))IntGetProcAddress("glPixelStorei");
  if (!_ptrc_glPixelStorei)
    numFailed++;
  _ptrc_glPixelTransferf = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat))IntGetProcAddress("glPixelTransferf");
  if (!_ptrc_glPixelTransferf)
    numFailed++;
  _ptrc_glPixelTransferi = (void(CODEGEN_FUNCPTR*)(GLenum, GLint))IntGetProcAddress("glPixelTransferi");
  if (!_ptrc_glPixelTransferi)
    numFailed++;
  _ptrc_glPixelZoom = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat))IntGetProcAddress("glPixelZoom");
  if (!_ptrc_glPixelZoom)
    numFailed++;
  _ptrc_glPointSize = (void(CODEGEN_FUNCPTR*)(GLfloat))IntGetProcAddress("glPointSize");
  if (!_ptrc_glPointSize)
    numFailed++;
  _ptrc_glPolygonMode = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum))IntGetProcAddress("glPolygonMode");
  if (!_ptrc_glPolygonMode)
    numFailed++;
  _ptrc_glPolygonStipple = (void(CODEGEN_FUNCPTR*)(const GLubyte*))IntGetProcAddress("glPolygonStipple");
  if (!_ptrc_glPolygonStipple)
    numFailed++;
  _ptrc_glPopAttrib = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glPopAttrib");
  if (!_ptrc_glPopAttrib)
    numFailed++;
  _ptrc_glPopMatrix = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glPopMatrix");
  if (!_ptrc_glPopMatrix)
    numFailed++;
  _ptrc_glPopName = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glPopName");
  if (!_ptrc_glPopName)
    numFailed++;
  _ptrc_glPushAttrib = (void(CODEGEN_FUNCPTR*)(GLbitfield))IntGetProcAddress("glPushAttrib");
  if (!_ptrc_glPushAttrib)
    numFailed++;
  _ptrc_glPushMatrix = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glPushMatrix");
  if (!_ptrc_glPushMatrix)
    numFailed++;
  _ptrc_glPushName = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glPushName");
  if (!_ptrc_glPushName)
    numFailed++;
  _ptrc_glRasterPos2d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble))IntGetProcAddress("glRasterPos2d");
  if (!_ptrc_glRasterPos2d)
    numFailed++;
  _ptrc_glRasterPos2dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glRasterPos2dv");
  if (!_ptrc_glRasterPos2dv)
    numFailed++;
  _ptrc_glRasterPos2f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat))IntGetProcAddress("glRasterPos2f");
  if (!_ptrc_glRasterPos2f)
    numFailed++;
  _ptrc_glRasterPos2fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glRasterPos2fv");
  if (!_ptrc_glRasterPos2fv)
    numFailed++;
  _ptrc_glRasterPos2i = (void(CODEGEN_FUNCPTR*)(GLint, GLint))IntGetProcAddress("glRasterPos2i");
  if (!_ptrc_glRasterPos2i)
    numFailed++;
  _ptrc_glRasterPos2iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glRasterPos2iv");
  if (!_ptrc_glRasterPos2iv)
    numFailed++;
  _ptrc_glRasterPos2s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort))IntGetProcAddress("glRasterPos2s");
  if (!_ptrc_glRasterPos2s)
    numFailed++;
  _ptrc_glRasterPos2sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glRasterPos2sv");
  if (!_ptrc_glRasterPos2sv)
    numFailed++;
  _ptrc_glRasterPos3d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble))IntGetProcAddress("glRasterPos3d");
  if (!_ptrc_glRasterPos3d)
    numFailed++;
  _ptrc_glRasterPos3dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glRasterPos3dv");
  if (!_ptrc_glRasterPos3dv)
    numFailed++;
  _ptrc_glRasterPos3f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat))IntGetProcAddress("glRasterPos3f");
  if (!_ptrc_glRasterPos3f)
    numFailed++;
  _ptrc_glRasterPos3fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glRasterPos3fv");
  if (!_ptrc_glRasterPos3fv)
    numFailed++;
  _ptrc_glRasterPos3i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint))IntGetProcAddress("glRasterPos3i");
  if (!_ptrc_glRasterPos3i)
    numFailed++;
  _ptrc_glRasterPos3iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glRasterPos3iv");
  if (!_ptrc_glRasterPos3iv)
    numFailed++;
  _ptrc_glRasterPos3s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort))IntGetProcAddress("glRasterPos3s");
  if (!_ptrc_glRasterPos3s)
    numFailed++;
  _ptrc_glRasterPos3sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glRasterPos3sv");
  if (!_ptrc_glRasterPos3sv)
    numFailed++;
  _ptrc_glRasterPos4d =
      (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glRasterPos4d");
  if (!_ptrc_glRasterPos4d)
    numFailed++;
  _ptrc_glRasterPos4dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glRasterPos4dv");
  if (!_ptrc_glRasterPos4dv)
    numFailed++;
  _ptrc_glRasterPos4f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glRasterPos4f");
  if (!_ptrc_glRasterPos4f)
    numFailed++;
  _ptrc_glRasterPos4fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glRasterPos4fv");
  if (!_ptrc_glRasterPos4fv)
    numFailed++;
  _ptrc_glRasterPos4i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint, GLint))IntGetProcAddress("glRasterPos4i");
  if (!_ptrc_glRasterPos4i)
    numFailed++;
  _ptrc_glRasterPos4iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glRasterPos4iv");
  if (!_ptrc_glRasterPos4iv)
    numFailed++;
  _ptrc_glRasterPos4s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort, GLshort))IntGetProcAddress("glRasterPos4s");
  if (!_ptrc_glRasterPos4s)
    numFailed++;
  _ptrc_glRasterPos4sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glRasterPos4sv");
  if (!_ptrc_glRasterPos4sv)
    numFailed++;
  _ptrc_glReadBuffer = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glReadBuffer");
  if (!_ptrc_glReadBuffer)
    numFailed++;
  _ptrc_glReadPixels =
      (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void*))IntGetProcAddress("glReadPixels");
  if (!_ptrc_glReadPixels)
    numFailed++;
  _ptrc_glRectd = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glRectd");
  if (!_ptrc_glRectd)
    numFailed++;
  _ptrc_glRectdv = (void(CODEGEN_FUNCPTR*)(const GLdouble*, const GLdouble*))IntGetProcAddress("glRectdv");
  if (!_ptrc_glRectdv)
    numFailed++;
  _ptrc_glRectf = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glRectf");
  if (!_ptrc_glRectf)
    numFailed++;
  _ptrc_glRectfv = (void(CODEGEN_FUNCPTR*)(const GLfloat*, const GLfloat*))IntGetProcAddress("glRectfv");
  if (!_ptrc_glRectfv)
    numFailed++;
  _ptrc_glRecti = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint, GLint))IntGetProcAddress("glRecti");
  if (!_ptrc_glRecti)
    numFailed++;
  _ptrc_glRectiv = (void(CODEGEN_FUNCPTR*)(const GLint*, const GLint*))IntGetProcAddress("glRectiv");
  if (!_ptrc_glRectiv)
    numFailed++;
  _ptrc_glRects = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort, GLshort))IntGetProcAddress("glRects");
  if (!_ptrc_glRects)
    numFailed++;
  _ptrc_glRectsv = (void(CODEGEN_FUNCPTR*)(const GLshort*, const GLshort*))IntGetProcAddress("glRectsv");
  if (!_ptrc_glRectsv)
    numFailed++;
  _ptrc_glRenderMode = (GLint(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glRenderMode");
  if (!_ptrc_glRenderMode)
    numFailed++;
  _ptrc_glRotated = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glRotated");
  if (!_ptrc_glRotated)
    numFailed++;
  _ptrc_glRotatef = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glRotatef");
  if (!_ptrc_glRotatef)
    numFailed++;
  _ptrc_glScaled = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble))IntGetProcAddress("glScaled");
  if (!_ptrc_glScaled)
    numFailed++;
  _ptrc_glScalef = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat))IntGetProcAddress("glScalef");
  if (!_ptrc_glScalef)
    numFailed++;
  _ptrc_glScissor = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLsizei, GLsizei))IntGetProcAddress("glScissor");
  if (!_ptrc_glScissor)
    numFailed++;
  _ptrc_glSelectBuffer = (void(CODEGEN_FUNCPTR*)(GLsizei, GLuint*))IntGetProcAddress("glSelectBuffer");
  if (!_ptrc_glSelectBuffer)
    numFailed++;
  _ptrc_glShadeModel = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glShadeModel");
  if (!_ptrc_glShadeModel)
    numFailed++;
  _ptrc_glStencilFunc = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLuint))IntGetProcAddress("glStencilFunc");
  if (!_ptrc_glStencilFunc)
    numFailed++;
  _ptrc_glStencilMask = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glStencilMask");
  if (!_ptrc_glStencilMask)
    numFailed++;
  _ptrc_glStencilOp = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLenum))IntGetProcAddress("glStencilOp");
  if (!_ptrc_glStencilOp)
    numFailed++;
  _ptrc_glTexCoord1d = (void(CODEGEN_FUNCPTR*)(GLdouble))IntGetProcAddress("glTexCoord1d");
  if (!_ptrc_glTexCoord1d)
    numFailed++;
  _ptrc_glTexCoord1dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glTexCoord1dv");
  if (!_ptrc_glTexCoord1dv)
    numFailed++;
  _ptrc_glTexCoord1f = (void(CODEGEN_FUNCPTR*)(GLfloat))IntGetProcAddress("glTexCoord1f");
  if (!_ptrc_glTexCoord1f)
    numFailed++;
  _ptrc_glTexCoord1fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glTexCoord1fv");
  if (!_ptrc_glTexCoord1fv)
    numFailed++;
  _ptrc_glTexCoord1i = (void(CODEGEN_FUNCPTR*)(GLint))IntGetProcAddress("glTexCoord1i");
  if (!_ptrc_glTexCoord1i)
    numFailed++;
  _ptrc_glTexCoord1iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glTexCoord1iv");
  if (!_ptrc_glTexCoord1iv)
    numFailed++;
  _ptrc_glTexCoord1s = (void(CODEGEN_FUNCPTR*)(GLshort))IntGetProcAddress("glTexCoord1s");
  if (!_ptrc_glTexCoord1s)
    numFailed++;
  _ptrc_glTexCoord1sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glTexCoord1sv");
  if (!_ptrc_glTexCoord1sv)
    numFailed++;
  _ptrc_glTexCoord2d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble))IntGetProcAddress("glTexCoord2d");
  if (!_ptrc_glTexCoord2d)
    numFailed++;
  _ptrc_glTexCoord2dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glTexCoord2dv");
  if (!_ptrc_glTexCoord2dv)
    numFailed++;
  _ptrc_glTexCoord2f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat))IntGetProcAddress("glTexCoord2f");
  if (!_ptrc_glTexCoord2f)
    numFailed++;
  _ptrc_glTexCoord2fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glTexCoord2fv");
  if (!_ptrc_glTexCoord2fv)
    numFailed++;
  _ptrc_glTexCoord2i = (void(CODEGEN_FUNCPTR*)(GLint, GLint))IntGetProcAddress("glTexCoord2i");
  if (!_ptrc_glTexCoord2i)
    numFailed++;
  _ptrc_glTexCoord2iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glTexCoord2iv");
  if (!_ptrc_glTexCoord2iv)
    numFailed++;
  _ptrc_glTexCoord2s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort))IntGetProcAddress("glTexCoord2s");
  if (!_ptrc_glTexCoord2s)
    numFailed++;
  _ptrc_glTexCoord2sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glTexCoord2sv");
  if (!_ptrc_glTexCoord2sv)
    numFailed++;
  _ptrc_glTexCoord3d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble))IntGetProcAddress("glTexCoord3d");
  if (!_ptrc_glTexCoord3d)
    numFailed++;
  _ptrc_glTexCoord3dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glTexCoord3dv");
  if (!_ptrc_glTexCoord3dv)
    numFailed++;
  _ptrc_glTexCoord3f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat))IntGetProcAddress("glTexCoord3f");
  if (!_ptrc_glTexCoord3f)
    numFailed++;
  _ptrc_glTexCoord3fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glTexCoord3fv");
  if (!_ptrc_glTexCoord3fv)
    numFailed++;
  _ptrc_glTexCoord3i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint))IntGetProcAddress("glTexCoord3i");
  if (!_ptrc_glTexCoord3i)
    numFailed++;
  _ptrc_glTexCoord3iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glTexCoord3iv");
  if (!_ptrc_glTexCoord3iv)
    numFailed++;
  _ptrc_glTexCoord3s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort))IntGetProcAddress("glTexCoord3s");
  if (!_ptrc_glTexCoord3s)
    numFailed++;
  _ptrc_glTexCoord3sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glTexCoord3sv");
  if (!_ptrc_glTexCoord3sv)
    numFailed++;
  _ptrc_glTexCoord4d =
      (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glTexCoord4d");
  if (!_ptrc_glTexCoord4d)
    numFailed++;
  _ptrc_glTexCoord4dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glTexCoord4dv");
  if (!_ptrc_glTexCoord4dv)
    numFailed++;
  _ptrc_glTexCoord4f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glTexCoord4f");
  if (!_ptrc_glTexCoord4f)
    numFailed++;
  _ptrc_glTexCoord4fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glTexCoord4fv");
  if (!_ptrc_glTexCoord4fv)
    numFailed++;
  _ptrc_glTexCoord4i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint, GLint))IntGetProcAddress("glTexCoord4i");
  if (!_ptrc_glTexCoord4i)
    numFailed++;
  _ptrc_glTexCoord4iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glTexCoord4iv");
  if (!_ptrc_glTexCoord4iv)
    numFailed++;
  _ptrc_glTexCoord4s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort, GLshort))IntGetProcAddress("glTexCoord4s");
  if (!_ptrc_glTexCoord4s)
    numFailed++;
  _ptrc_glTexCoord4sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glTexCoord4sv");
  if (!_ptrc_glTexCoord4sv)
    numFailed++;
  _ptrc_glTexEnvf = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat))IntGetProcAddress("glTexEnvf");
  if (!_ptrc_glTexEnvf)
    numFailed++;
  _ptrc_glTexEnvfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLfloat*))IntGetProcAddress("glTexEnvfv");
  if (!_ptrc_glTexEnvfv)
    numFailed++;
  _ptrc_glTexEnvi = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint))IntGetProcAddress("glTexEnvi");
  if (!_ptrc_glTexEnvi)
    numFailed++;
  _ptrc_glTexEnviv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLint*))IntGetProcAddress("glTexEnviv");
  if (!_ptrc_glTexEnviv)
    numFailed++;
  _ptrc_glTexGend = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLdouble))IntGetProcAddress("glTexGend");
  if (!_ptrc_glTexGend)
    numFailed++;
  _ptrc_glTexGendv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLdouble*))IntGetProcAddress("glTexGendv");
  if (!_ptrc_glTexGendv)
    numFailed++;
  _ptrc_glTexGenf = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat))IntGetProcAddress("glTexGenf");
  if (!_ptrc_glTexGenf)
    numFailed++;
  _ptrc_glTexGenfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLfloat*))IntGetProcAddress("glTexGenfv");
  if (!_ptrc_glTexGenfv)
    numFailed++;
  _ptrc_glTexGeni = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint))IntGetProcAddress("glTexGeni");
  if (!_ptrc_glTexGeni)
    numFailed++;
  _ptrc_glTexGeniv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLint*))IntGetProcAddress("glTexGeniv");
  if (!_ptrc_glTexGeniv)
    numFailed++;
  _ptrc_glTexImage1D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum,
                                               const void*))IntGetProcAddress("glTexImage1D");
  if (!_ptrc_glTexImage1D)
    numFailed++;
  _ptrc_glTexImage2D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum,
                                               const void*))IntGetProcAddress("glTexImage2D");
  if (!_ptrc_glTexImage2D)
    numFailed++;
  _ptrc_glTexParameterf = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLfloat))IntGetProcAddress("glTexParameterf");
  if (!_ptrc_glTexParameterf)
    numFailed++;
  _ptrc_glTexParameterfv =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLfloat*))IntGetProcAddress("glTexParameterfv");
  if (!_ptrc_glTexParameterfv)
    numFailed++;
  _ptrc_glTexParameteri = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint))IntGetProcAddress("glTexParameteri");
  if (!_ptrc_glTexParameteri)
    numFailed++;
  _ptrc_glTexParameteriv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLint*))IntGetProcAddress("glTexParameteriv");
  if (!_ptrc_glTexParameteriv)
    numFailed++;
  _ptrc_glTranslated = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble))IntGetProcAddress("glTranslated");
  if (!_ptrc_glTranslated)
    numFailed++;
  _ptrc_glTranslatef = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat))IntGetProcAddress("glTranslatef");
  if (!_ptrc_glTranslatef)
    numFailed++;
  _ptrc_glVertex2d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble))IntGetProcAddress("glVertex2d");
  if (!_ptrc_glVertex2d)
    numFailed++;
  _ptrc_glVertex2dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glVertex2dv");
  if (!_ptrc_glVertex2dv)
    numFailed++;
  _ptrc_glVertex2f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat))IntGetProcAddress("glVertex2f");
  if (!_ptrc_glVertex2f)
    numFailed++;
  _ptrc_glVertex2fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glVertex2fv");
  if (!_ptrc_glVertex2fv)
    numFailed++;
  _ptrc_glVertex2i = (void(CODEGEN_FUNCPTR*)(GLint, GLint))IntGetProcAddress("glVertex2i");
  if (!_ptrc_glVertex2i)
    numFailed++;
  _ptrc_glVertex2iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glVertex2iv");
  if (!_ptrc_glVertex2iv)
    numFailed++;
  _ptrc_glVertex2s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort))IntGetProcAddress("glVertex2s");
  if (!_ptrc_glVertex2s)
    numFailed++;
  _ptrc_glVertex2sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glVertex2sv");
  if (!_ptrc_glVertex2sv)
    numFailed++;
  _ptrc_glVertex3d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble))IntGetProcAddress("glVertex3d");
  if (!_ptrc_glVertex3d)
    numFailed++;
  _ptrc_glVertex3dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glVertex3dv");
  if (!_ptrc_glVertex3dv)
    numFailed++;
  _ptrc_glVertex3f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat))IntGetProcAddress("glVertex3f");
  if (!_ptrc_glVertex3f)
    numFailed++;
  _ptrc_glVertex3fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glVertex3fv");
  if (!_ptrc_glVertex3fv)
    numFailed++;
  _ptrc_glVertex3i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint))IntGetProcAddress("glVertex3i");
  if (!_ptrc_glVertex3i)
    numFailed++;
  _ptrc_glVertex3iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glVertex3iv");
  if (!_ptrc_glVertex3iv)
    numFailed++;
  _ptrc_glVertex3s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort))IntGetProcAddress("glVertex3s");
  if (!_ptrc_glVertex3s)
    numFailed++;
  _ptrc_glVertex3sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glVertex3sv");
  if (!_ptrc_glVertex3sv)
    numFailed++;
  _ptrc_glVertex4d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glVertex4d");
  if (!_ptrc_glVertex4d)
    numFailed++;
  _ptrc_glVertex4dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glVertex4dv");
  if (!_ptrc_glVertex4dv)
    numFailed++;
  _ptrc_glVertex4f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glVertex4f");
  if (!_ptrc_glVertex4f)
    numFailed++;
  _ptrc_glVertex4fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glVertex4fv");
  if (!_ptrc_glVertex4fv)
    numFailed++;
  _ptrc_glVertex4i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint, GLint))IntGetProcAddress("glVertex4i");
  if (!_ptrc_glVertex4i)
    numFailed++;
  _ptrc_glVertex4iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glVertex4iv");
  if (!_ptrc_glVertex4iv)
    numFailed++;
  _ptrc_glVertex4s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort, GLshort))IntGetProcAddress("glVertex4s");
  if (!_ptrc_glVertex4s)
    numFailed++;
  _ptrc_glVertex4sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glVertex4sv");
  if (!_ptrc_glVertex4sv)
    numFailed++;
  _ptrc_glViewport = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLsizei, GLsizei))IntGetProcAddress("glViewport");
  if (!_ptrc_glViewport)
    numFailed++;
  _ptrc_glAreTexturesResident =
      (GLboolean(CODEGEN_FUNCPTR*)(GLsizei, const GLuint*, GLboolean*))IntGetProcAddress("glAreTexturesResident");
  if (!_ptrc_glAreTexturesResident)
    numFailed++;
  _ptrc_glArrayElement = (void(CODEGEN_FUNCPTR*)(GLint))IntGetProcAddress("glArrayElement");
  if (!_ptrc_glArrayElement)
    numFailed++;
  _ptrc_glBindTexture = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glBindTexture");
  if (!_ptrc_glBindTexture)
    numFailed++;
  _ptrc_glColorPointer =
      (void(CODEGEN_FUNCPTR*)(GLint, GLenum, GLsizei, const void*))IntGetProcAddress("glColorPointer");
  if (!_ptrc_glColorPointer)
    numFailed++;
  _ptrc_glCopyTexImage1D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLenum, GLint, GLint, GLsizei,
                                                   GLint))IntGetProcAddress("glCopyTexImage1D");
  if (!_ptrc_glCopyTexImage1D)
    numFailed++;
  _ptrc_glCopyTexImage2D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei,
                                                   GLint))IntGetProcAddress("glCopyTexImage2D");
  if (!_ptrc_glCopyTexImage2D)
    numFailed++;
  _ptrc_glCopyTexSubImage1D =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLint, GLint, GLsizei))IntGetProcAddress("glCopyTexSubImage1D");
  if (!_ptrc_glCopyTexSubImage1D)
    numFailed++;
  _ptrc_glCopyTexSubImage2D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei,
                                                      GLsizei))IntGetProcAddress("glCopyTexSubImage2D");
  if (!_ptrc_glCopyTexSubImage2D)
    numFailed++;
  _ptrc_glDeleteTextures = (void(CODEGEN_FUNCPTR*)(GLsizei, const GLuint*))IntGetProcAddress("glDeleteTextures");
  if (!_ptrc_glDeleteTextures)
    numFailed++;
  _ptrc_glDisableClientState = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glDisableClientState");
  if (!_ptrc_glDisableClientState)
    numFailed++;
  _ptrc_glDrawArrays = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLsizei))IntGetProcAddress("glDrawArrays");
  if (!_ptrc_glDrawArrays)
    numFailed++;
  _ptrc_glDrawElements =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLsizei, GLenum, const void*))IntGetProcAddress("glDrawElements");
  if (!_ptrc_glDrawElements)
    numFailed++;
  _ptrc_glEdgeFlagPointer = (void(CODEGEN_FUNCPTR*)(GLsizei, const void*))IntGetProcAddress("glEdgeFlagPointer");
  if (!_ptrc_glEdgeFlagPointer)
    numFailed++;
  _ptrc_glEnableClientState = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glEnableClientState");
  if (!_ptrc_glEnableClientState)
    numFailed++;
  _ptrc_glGenTextures = (void(CODEGEN_FUNCPTR*)(GLsizei, GLuint*))IntGetProcAddress("glGenTextures");
  if (!_ptrc_glGenTextures)
    numFailed++;
  _ptrc_glGetPointerv = (void(CODEGEN_FUNCPTR*)(GLenum, void**))IntGetProcAddress("glGetPointerv");
  if (!_ptrc_glGetPointerv)
    numFailed++;
  _ptrc_glIndexPointer = (void(CODEGEN_FUNCPTR*)(GLenum, GLsizei, const void*))IntGetProcAddress("glIndexPointer");
  if (!_ptrc_glIndexPointer)
    numFailed++;
  _ptrc_glIndexub = (void(CODEGEN_FUNCPTR*)(GLubyte))IntGetProcAddress("glIndexub");
  if (!_ptrc_glIndexub)
    numFailed++;
  _ptrc_glIndexubv = (void(CODEGEN_FUNCPTR*)(const GLubyte*))IntGetProcAddress("glIndexubv");
  if (!_ptrc_glIndexubv)
    numFailed++;
  _ptrc_glInterleavedArrays =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLsizei, const void*))IntGetProcAddress("glInterleavedArrays");
  if (!_ptrc_glInterleavedArrays)
    numFailed++;
  _ptrc_glIsTexture = (GLboolean(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glIsTexture");
  if (!_ptrc_glIsTexture)
    numFailed++;
  _ptrc_glNormalPointer = (void(CODEGEN_FUNCPTR*)(GLenum, GLsizei, const void*))IntGetProcAddress("glNormalPointer");
  if (!_ptrc_glNormalPointer)
    numFailed++;
  _ptrc_glPolygonOffset = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat))IntGetProcAddress("glPolygonOffset");
  if (!_ptrc_glPolygonOffset)
    numFailed++;
  _ptrc_glPopClientAttrib = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glPopClientAttrib");
  if (!_ptrc_glPopClientAttrib)
    numFailed++;
  _ptrc_glPrioritizeTextures =
      (void(CODEGEN_FUNCPTR*)(GLsizei, const GLuint*, const GLfloat*))IntGetProcAddress("glPrioritizeTextures");
  if (!_ptrc_glPrioritizeTextures)
    numFailed++;
  _ptrc_glPushClientAttrib = (void(CODEGEN_FUNCPTR*)(GLbitfield))IntGetProcAddress("glPushClientAttrib");
  if (!_ptrc_glPushClientAttrib)
    numFailed++;
  _ptrc_glTexCoordPointer =
      (void(CODEGEN_FUNCPTR*)(GLint, GLenum, GLsizei, const void*))IntGetProcAddress("glTexCoordPointer");
  if (!_ptrc_glTexCoordPointer)
    numFailed++;
  _ptrc_glTexSubImage1D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum,
                                                  const void*))IntGetProcAddress("glTexSubImage1D");
  if (!_ptrc_glTexSubImage1D)
    numFailed++;
  _ptrc_glTexSubImage2D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum,
                                                  const void*))IntGetProcAddress("glTexSubImage2D");
  if (!_ptrc_glTexSubImage2D)
    numFailed++;
  _ptrc_glVertexPointer =
      (void(CODEGEN_FUNCPTR*)(GLint, GLenum, GLsizei, const void*))IntGetProcAddress("glVertexPointer");
  if (!_ptrc_glVertexPointer)
    numFailed++;
  _ptrc_glCopyTexSubImage3D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei,
                                                      GLsizei))IntGetProcAddress("glCopyTexSubImage3D");
  if (!_ptrc_glCopyTexSubImage3D)
    numFailed++;
  _ptrc_glDrawRangeElements = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint, GLuint, GLsizei, GLenum,
                                                      const void*))IntGetProcAddress("glDrawRangeElements");
  if (!_ptrc_glDrawRangeElements)
    numFailed++;
  _ptrc_glTexImage3D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum,
                                               const void*))IntGetProcAddress("glTexImage3D");
  if (!_ptrc_glTexImage3D)
    numFailed++;
  _ptrc_glTexSubImage3D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum,
                                                  GLenum, const void*))IntGetProcAddress("glTexSubImage3D");
  if (!_ptrc_glTexSubImage3D)
    numFailed++;
  _ptrc_glActiveTexture = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glActiveTexture");
  if (!_ptrc_glActiveTexture)
    numFailed++;
  _ptrc_glClientActiveTexture = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glClientActiveTexture");
  if (!_ptrc_glClientActiveTexture)
    numFailed++;
  _ptrc_glCompressedTexImage1D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei,
                                                         const void*))IntGetProcAddress("glCompressedTexImage1D");
  if (!_ptrc_glCompressedTexImage1D)
    numFailed++;
  _ptrc_glCompressedTexImage2D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei,
                                                         const void*))IntGetProcAddress("glCompressedTexImage2D");
  if (!_ptrc_glCompressedTexImage2D)
    numFailed++;
  _ptrc_glCompressedTexImage3D =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei,
                              const void*))IntGetProcAddress("glCompressedTexImage3D");
  if (!_ptrc_glCompressedTexImage3D)
    numFailed++;
  _ptrc_glCompressedTexSubImage1D = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei,
                                                            const void*))IntGetProcAddress("glCompressedTexSubImage1D");
  if (!_ptrc_glCompressedTexSubImage1D)
    numFailed++;
  _ptrc_glCompressedTexSubImage2D =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei,
                              const void*))IntGetProcAddress("glCompressedTexSubImage2D");
  if (!_ptrc_glCompressedTexSubImage2D)
    numFailed++;
  _ptrc_glCompressedTexSubImage3D =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei,
                              const void*))IntGetProcAddress("glCompressedTexSubImage3D");
  if (!_ptrc_glCompressedTexSubImage3D)
    numFailed++;
  _ptrc_glGetCompressedTexImage =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLint, void*))IntGetProcAddress("glGetCompressedTexImage");
  if (!_ptrc_glGetCompressedTexImage)
    numFailed++;
  _ptrc_glLoadTransposeMatrixd = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glLoadTransposeMatrixd");
  if (!_ptrc_glLoadTransposeMatrixd)
    numFailed++;
  _ptrc_glLoadTransposeMatrixf = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glLoadTransposeMatrixf");
  if (!_ptrc_glLoadTransposeMatrixf)
    numFailed++;
  _ptrc_glMultTransposeMatrixd = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glMultTransposeMatrixd");
  if (!_ptrc_glMultTransposeMatrixd)
    numFailed++;
  _ptrc_glMultTransposeMatrixf = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glMultTransposeMatrixf");
  if (!_ptrc_glMultTransposeMatrixf)
    numFailed++;
  _ptrc_glMultiTexCoord1d = (void(CODEGEN_FUNCPTR*)(GLenum, GLdouble))IntGetProcAddress("glMultiTexCoord1d");
  if (!_ptrc_glMultiTexCoord1d)
    numFailed++;
  _ptrc_glMultiTexCoord1dv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLdouble*))IntGetProcAddress("glMultiTexCoord1dv");
  if (!_ptrc_glMultiTexCoord1dv)
    numFailed++;
  _ptrc_glMultiTexCoord1f = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat))IntGetProcAddress("glMultiTexCoord1f");
  if (!_ptrc_glMultiTexCoord1f)
    numFailed++;
  _ptrc_glMultiTexCoord1fv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLfloat*))IntGetProcAddress("glMultiTexCoord1fv");
  if (!_ptrc_glMultiTexCoord1fv)
    numFailed++;
  _ptrc_glMultiTexCoord1i = (void(CODEGEN_FUNCPTR*)(GLenum, GLint))IntGetProcAddress("glMultiTexCoord1i");
  if (!_ptrc_glMultiTexCoord1i)
    numFailed++;
  _ptrc_glMultiTexCoord1iv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLint*))IntGetProcAddress("glMultiTexCoord1iv");
  if (!_ptrc_glMultiTexCoord1iv)
    numFailed++;
  _ptrc_glMultiTexCoord1s = (void(CODEGEN_FUNCPTR*)(GLenum, GLshort))IntGetProcAddress("glMultiTexCoord1s");
  if (!_ptrc_glMultiTexCoord1s)
    numFailed++;
  _ptrc_glMultiTexCoord1sv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLshort*))IntGetProcAddress("glMultiTexCoord1sv");
  if (!_ptrc_glMultiTexCoord1sv)
    numFailed++;
  _ptrc_glMultiTexCoord2d = (void(CODEGEN_FUNCPTR*)(GLenum, GLdouble, GLdouble))IntGetProcAddress("glMultiTexCoord2d");
  if (!_ptrc_glMultiTexCoord2d)
    numFailed++;
  _ptrc_glMultiTexCoord2dv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLdouble*))IntGetProcAddress("glMultiTexCoord2dv");
  if (!_ptrc_glMultiTexCoord2dv)
    numFailed++;
  _ptrc_glMultiTexCoord2f = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat, GLfloat))IntGetProcAddress("glMultiTexCoord2f");
  if (!_ptrc_glMultiTexCoord2f)
    numFailed++;
  _ptrc_glMultiTexCoord2fv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLfloat*))IntGetProcAddress("glMultiTexCoord2fv");
  if (!_ptrc_glMultiTexCoord2fv)
    numFailed++;
  _ptrc_glMultiTexCoord2i = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint))IntGetProcAddress("glMultiTexCoord2i");
  if (!_ptrc_glMultiTexCoord2i)
    numFailed++;
  _ptrc_glMultiTexCoord2iv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLint*))IntGetProcAddress("glMultiTexCoord2iv");
  if (!_ptrc_glMultiTexCoord2iv)
    numFailed++;
  _ptrc_glMultiTexCoord2s = (void(CODEGEN_FUNCPTR*)(GLenum, GLshort, GLshort))IntGetProcAddress("glMultiTexCoord2s");
  if (!_ptrc_glMultiTexCoord2s)
    numFailed++;
  _ptrc_glMultiTexCoord2sv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLshort*))IntGetProcAddress("glMultiTexCoord2sv");
  if (!_ptrc_glMultiTexCoord2sv)
    numFailed++;
  _ptrc_glMultiTexCoord3d =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glMultiTexCoord3d");
  if (!_ptrc_glMultiTexCoord3d)
    numFailed++;
  _ptrc_glMultiTexCoord3dv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLdouble*))IntGetProcAddress("glMultiTexCoord3dv");
  if (!_ptrc_glMultiTexCoord3dv)
    numFailed++;
  _ptrc_glMultiTexCoord3f =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glMultiTexCoord3f");
  if (!_ptrc_glMultiTexCoord3f)
    numFailed++;
  _ptrc_glMultiTexCoord3fv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLfloat*))IntGetProcAddress("glMultiTexCoord3fv");
  if (!_ptrc_glMultiTexCoord3fv)
    numFailed++;
  _ptrc_glMultiTexCoord3i = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLint))IntGetProcAddress("glMultiTexCoord3i");
  if (!_ptrc_glMultiTexCoord3i)
    numFailed++;
  _ptrc_glMultiTexCoord3iv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLint*))IntGetProcAddress("glMultiTexCoord3iv");
  if (!_ptrc_glMultiTexCoord3iv)
    numFailed++;
  _ptrc_glMultiTexCoord3s =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLshort, GLshort, GLshort))IntGetProcAddress("glMultiTexCoord3s");
  if (!_ptrc_glMultiTexCoord3s)
    numFailed++;
  _ptrc_glMultiTexCoord3sv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLshort*))IntGetProcAddress("glMultiTexCoord3sv");
  if (!_ptrc_glMultiTexCoord3sv)
    numFailed++;
  _ptrc_glMultiTexCoord4d =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glMultiTexCoord4d");
  if (!_ptrc_glMultiTexCoord4d)
    numFailed++;
  _ptrc_glMultiTexCoord4dv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLdouble*))IntGetProcAddress("glMultiTexCoord4dv");
  if (!_ptrc_glMultiTexCoord4dv)
    numFailed++;
  _ptrc_glMultiTexCoord4f =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glMultiTexCoord4f");
  if (!_ptrc_glMultiTexCoord4f)
    numFailed++;
  _ptrc_glMultiTexCoord4fv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLfloat*))IntGetProcAddress("glMultiTexCoord4fv");
  if (!_ptrc_glMultiTexCoord4fv)
    numFailed++;
  _ptrc_glMultiTexCoord4i =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLint, GLint, GLint))IntGetProcAddress("glMultiTexCoord4i");
  if (!_ptrc_glMultiTexCoord4i)
    numFailed++;
  _ptrc_glMultiTexCoord4iv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLint*))IntGetProcAddress("glMultiTexCoord4iv");
  if (!_ptrc_glMultiTexCoord4iv)
    numFailed++;
  _ptrc_glMultiTexCoord4s =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLshort, GLshort, GLshort, GLshort))IntGetProcAddress("glMultiTexCoord4s");
  if (!_ptrc_glMultiTexCoord4s)
    numFailed++;
  _ptrc_glMultiTexCoord4sv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLshort*))IntGetProcAddress("glMultiTexCoord4sv");
  if (!_ptrc_glMultiTexCoord4sv)
    numFailed++;
  _ptrc_glSampleCoverage = (void(CODEGEN_FUNCPTR*)(GLfloat, GLboolean))IntGetProcAddress("glSampleCoverage");
  if (!_ptrc_glSampleCoverage)
    numFailed++;
  _ptrc_glBlendColor = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glBlendColor");
  if (!_ptrc_glBlendColor)
    numFailed++;
  _ptrc_glBlendEquation = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glBlendEquation");
  if (!_ptrc_glBlendEquation)
    numFailed++;
  _ptrc_glBlendFuncSeparate =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLenum, GLenum))IntGetProcAddress("glBlendFuncSeparate");
  if (!_ptrc_glBlendFuncSeparate)
    numFailed++;
  _ptrc_glFogCoordPointer =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLsizei, const void*))IntGetProcAddress("glFogCoordPointer");
  if (!_ptrc_glFogCoordPointer)
    numFailed++;
  _ptrc_glFogCoordd = (void(CODEGEN_FUNCPTR*)(GLdouble))IntGetProcAddress("glFogCoordd");
  if (!_ptrc_glFogCoordd)
    numFailed++;
  _ptrc_glFogCoorddv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glFogCoorddv");
  if (!_ptrc_glFogCoorddv)
    numFailed++;
  _ptrc_glFogCoordf = (void(CODEGEN_FUNCPTR*)(GLfloat))IntGetProcAddress("glFogCoordf");
  if (!_ptrc_glFogCoordf)
    numFailed++;
  _ptrc_glFogCoordfv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glFogCoordfv");
  if (!_ptrc_glFogCoordfv)
    numFailed++;
  _ptrc_glMultiDrawArrays =
      (void(CODEGEN_FUNCPTR*)(GLenum, const GLint*, const GLsizei*, GLsizei))IntGetProcAddress("glMultiDrawArrays");
  if (!_ptrc_glMultiDrawArrays)
    numFailed++;
  _ptrc_glMultiDrawElements = (void(CODEGEN_FUNCPTR*)(GLenum, const GLsizei*, GLenum, const void* const*,
                                                      GLsizei))IntGetProcAddress("glMultiDrawElements");
  if (!_ptrc_glMultiDrawElements)
    numFailed++;
  _ptrc_glPointParameterf = (void(CODEGEN_FUNCPTR*)(GLenum, GLfloat))IntGetProcAddress("glPointParameterf");
  if (!_ptrc_glPointParameterf)
    numFailed++;
  _ptrc_glPointParameterfv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLfloat*))IntGetProcAddress("glPointParameterfv");
  if (!_ptrc_glPointParameterfv)
    numFailed++;
  _ptrc_glPointParameteri = (void(CODEGEN_FUNCPTR*)(GLenum, GLint))IntGetProcAddress("glPointParameteri");
  if (!_ptrc_glPointParameteri)
    numFailed++;
  _ptrc_glPointParameteriv = (void(CODEGEN_FUNCPTR*)(GLenum, const GLint*))IntGetProcAddress("glPointParameteriv");
  if (!_ptrc_glPointParameteriv)
    numFailed++;
  _ptrc_glSecondaryColor3b = (void(CODEGEN_FUNCPTR*)(GLbyte, GLbyte, GLbyte))IntGetProcAddress("glSecondaryColor3b");
  if (!_ptrc_glSecondaryColor3b)
    numFailed++;
  _ptrc_glSecondaryColor3bv = (void(CODEGEN_FUNCPTR*)(const GLbyte*))IntGetProcAddress("glSecondaryColor3bv");
  if (!_ptrc_glSecondaryColor3bv)
    numFailed++;
  _ptrc_glSecondaryColor3d =
      (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble))IntGetProcAddress("glSecondaryColor3d");
  if (!_ptrc_glSecondaryColor3d)
    numFailed++;
  _ptrc_glSecondaryColor3dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glSecondaryColor3dv");
  if (!_ptrc_glSecondaryColor3dv)
    numFailed++;
  _ptrc_glSecondaryColor3f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat))IntGetProcAddress("glSecondaryColor3f");
  if (!_ptrc_glSecondaryColor3f)
    numFailed++;
  _ptrc_glSecondaryColor3fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glSecondaryColor3fv");
  if (!_ptrc_glSecondaryColor3fv)
    numFailed++;
  _ptrc_glSecondaryColor3i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint))IntGetProcAddress("glSecondaryColor3i");
  if (!_ptrc_glSecondaryColor3i)
    numFailed++;
  _ptrc_glSecondaryColor3iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glSecondaryColor3iv");
  if (!_ptrc_glSecondaryColor3iv)
    numFailed++;
  _ptrc_glSecondaryColor3s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort))IntGetProcAddress("glSecondaryColor3s");
  if (!_ptrc_glSecondaryColor3s)
    numFailed++;
  _ptrc_glSecondaryColor3sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glSecondaryColor3sv");
  if (!_ptrc_glSecondaryColor3sv)
    numFailed++;
  _ptrc_glSecondaryColor3ub =
      (void(CODEGEN_FUNCPTR*)(GLubyte, GLubyte, GLubyte))IntGetProcAddress("glSecondaryColor3ub");
  if (!_ptrc_glSecondaryColor3ub)
    numFailed++;
  _ptrc_glSecondaryColor3ubv = (void(CODEGEN_FUNCPTR*)(const GLubyte*))IntGetProcAddress("glSecondaryColor3ubv");
  if (!_ptrc_glSecondaryColor3ubv)
    numFailed++;
  _ptrc_glSecondaryColor3ui = (void(CODEGEN_FUNCPTR*)(GLuint, GLuint, GLuint))IntGetProcAddress("glSecondaryColor3ui");
  if (!_ptrc_glSecondaryColor3ui)
    numFailed++;
  _ptrc_glSecondaryColor3uiv = (void(CODEGEN_FUNCPTR*)(const GLuint*))IntGetProcAddress("glSecondaryColor3uiv");
  if (!_ptrc_glSecondaryColor3uiv)
    numFailed++;
  _ptrc_glSecondaryColor3us =
      (void(CODEGEN_FUNCPTR*)(GLushort, GLushort, GLushort))IntGetProcAddress("glSecondaryColor3us");
  if (!_ptrc_glSecondaryColor3us)
    numFailed++;
  _ptrc_glSecondaryColor3usv = (void(CODEGEN_FUNCPTR*)(const GLushort*))IntGetProcAddress("glSecondaryColor3usv");
  if (!_ptrc_glSecondaryColor3usv)
    numFailed++;
  _ptrc_glSecondaryColorPointer =
      (void(CODEGEN_FUNCPTR*)(GLint, GLenum, GLsizei, const void*))IntGetProcAddress("glSecondaryColorPointer");
  if (!_ptrc_glSecondaryColorPointer)
    numFailed++;
  _ptrc_glWindowPos2d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble))IntGetProcAddress("glWindowPos2d");
  if (!_ptrc_glWindowPos2d)
    numFailed++;
  _ptrc_glWindowPos2dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glWindowPos2dv");
  if (!_ptrc_glWindowPos2dv)
    numFailed++;
  _ptrc_glWindowPos2f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat))IntGetProcAddress("glWindowPos2f");
  if (!_ptrc_glWindowPos2f)
    numFailed++;
  _ptrc_glWindowPos2fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glWindowPos2fv");
  if (!_ptrc_glWindowPos2fv)
    numFailed++;
  _ptrc_glWindowPos2i = (void(CODEGEN_FUNCPTR*)(GLint, GLint))IntGetProcAddress("glWindowPos2i");
  if (!_ptrc_glWindowPos2i)
    numFailed++;
  _ptrc_glWindowPos2iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glWindowPos2iv");
  if (!_ptrc_glWindowPos2iv)
    numFailed++;
  _ptrc_glWindowPos2s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort))IntGetProcAddress("glWindowPos2s");
  if (!_ptrc_glWindowPos2s)
    numFailed++;
  _ptrc_glWindowPos2sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glWindowPos2sv");
  if (!_ptrc_glWindowPos2sv)
    numFailed++;
  _ptrc_glWindowPos3d = (void(CODEGEN_FUNCPTR*)(GLdouble, GLdouble, GLdouble))IntGetProcAddress("glWindowPos3d");
  if (!_ptrc_glWindowPos3d)
    numFailed++;
  _ptrc_glWindowPos3dv = (void(CODEGEN_FUNCPTR*)(const GLdouble*))IntGetProcAddress("glWindowPos3dv");
  if (!_ptrc_glWindowPos3dv)
    numFailed++;
  _ptrc_glWindowPos3f = (void(CODEGEN_FUNCPTR*)(GLfloat, GLfloat, GLfloat))IntGetProcAddress("glWindowPos3f");
  if (!_ptrc_glWindowPos3f)
    numFailed++;
  _ptrc_glWindowPos3fv = (void(CODEGEN_FUNCPTR*)(const GLfloat*))IntGetProcAddress("glWindowPos3fv");
  if (!_ptrc_glWindowPos3fv)
    numFailed++;
  _ptrc_glWindowPos3i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint))IntGetProcAddress("glWindowPos3i");
  if (!_ptrc_glWindowPos3i)
    numFailed++;
  _ptrc_glWindowPos3iv = (void(CODEGEN_FUNCPTR*)(const GLint*))IntGetProcAddress("glWindowPos3iv");
  if (!_ptrc_glWindowPos3iv)
    numFailed++;
  _ptrc_glWindowPos3s = (void(CODEGEN_FUNCPTR*)(GLshort, GLshort, GLshort))IntGetProcAddress("glWindowPos3s");
  if (!_ptrc_glWindowPos3s)
    numFailed++;
  _ptrc_glWindowPos3sv = (void(CODEGEN_FUNCPTR*)(const GLshort*))IntGetProcAddress("glWindowPos3sv");
  if (!_ptrc_glWindowPos3sv)
    numFailed++;
  _ptrc_glBeginQuery = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glBeginQuery");
  if (!_ptrc_glBeginQuery)
    numFailed++;
  _ptrc_glBindBuffer = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glBindBuffer");
  if (!_ptrc_glBindBuffer)
    numFailed++;
  _ptrc_glBufferData =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLsizeiptr, const void*, GLenum))IntGetProcAddress("glBufferData");
  if (!_ptrc_glBufferData)
    numFailed++;
  _ptrc_glBufferSubData =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLintptr, GLsizeiptr, const void*))IntGetProcAddress("glBufferSubData");
  if (!_ptrc_glBufferSubData)
    numFailed++;
  _ptrc_glDeleteBuffers = (void(CODEGEN_FUNCPTR*)(GLsizei, const GLuint*))IntGetProcAddress("glDeleteBuffers");
  if (!_ptrc_glDeleteBuffers)
    numFailed++;
  _ptrc_glDeleteQueries = (void(CODEGEN_FUNCPTR*)(GLsizei, const GLuint*))IntGetProcAddress("glDeleteQueries");
  if (!_ptrc_glDeleteQueries)
    numFailed++;
  _ptrc_glEndQuery = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glEndQuery");
  if (!_ptrc_glEndQuery)
    numFailed++;
  _ptrc_glGenBuffers = (void(CODEGEN_FUNCPTR*)(GLsizei, GLuint*))IntGetProcAddress("glGenBuffers");
  if (!_ptrc_glGenBuffers)
    numFailed++;
  _ptrc_glGenQueries = (void(CODEGEN_FUNCPTR*)(GLsizei, GLuint*))IntGetProcAddress("glGenQueries");
  if (!_ptrc_glGenQueries)
    numFailed++;
  _ptrc_glGetBufferParameteriv =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint*))IntGetProcAddress("glGetBufferParameteriv");
  if (!_ptrc_glGetBufferParameteriv)
    numFailed++;
  _ptrc_glGetBufferPointerv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, void**))IntGetProcAddress("glGetBufferPointerv");
  if (!_ptrc_glGetBufferPointerv)
    numFailed++;
  _ptrc_glGetBufferSubData =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLintptr, GLsizeiptr, void*))IntGetProcAddress("glGetBufferSubData");
  if (!_ptrc_glGetBufferSubData)
    numFailed++;
  _ptrc_glGetQueryObjectiv = (void(CODEGEN_FUNCPTR*)(GLuint, GLenum, GLint*))IntGetProcAddress("glGetQueryObjectiv");
  if (!_ptrc_glGetQueryObjectiv)
    numFailed++;
  _ptrc_glGetQueryObjectuiv = (void(CODEGEN_FUNCPTR*)(GLuint, GLenum, GLuint*))IntGetProcAddress("glGetQueryObjectuiv");
  if (!_ptrc_glGetQueryObjectuiv)
    numFailed++;
  _ptrc_glGetQueryiv = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint*))IntGetProcAddress("glGetQueryiv");
  if (!_ptrc_glGetQueryiv)
    numFailed++;
  _ptrc_glIsBuffer = (GLboolean(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glIsBuffer");
  if (!_ptrc_glIsBuffer)
    numFailed++;
  _ptrc_glIsQuery = (GLboolean(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glIsQuery");
  if (!_ptrc_glIsQuery)
    numFailed++;
  _ptrc_glMapBuffer = (void*(CODEGEN_FUNCPTR*)(GLenum, GLenum))IntGetProcAddress("glMapBuffer");
  if (!_ptrc_glMapBuffer)
    numFailed++;
  _ptrc_glUnmapBuffer = (GLboolean(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glUnmapBuffer");
  if (!_ptrc_glUnmapBuffer)
    numFailed++;
  _ptrc_glAttachShader = (void(CODEGEN_FUNCPTR*)(GLuint, GLuint))IntGetProcAddress("glAttachShader");
  if (!_ptrc_glAttachShader)
    numFailed++;
  _ptrc_glBindAttribLocation =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLuint, const GLchar*))IntGetProcAddress("glBindAttribLocation");
  if (!_ptrc_glBindAttribLocation)
    numFailed++;
  _ptrc_glBlendEquationSeparate = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum))IntGetProcAddress("glBlendEquationSeparate");
  if (!_ptrc_glBlendEquationSeparate)
    numFailed++;
  _ptrc_glCompileShader = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glCompileShader");
  if (!_ptrc_glCompileShader)
    numFailed++;
  _ptrc_glCreateProgram = (GLuint(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glCreateProgram");
  if (!_ptrc_glCreateProgram)
    numFailed++;
  _ptrc_glCreateShader = (GLuint(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glCreateShader");
  if (!_ptrc_glCreateShader)
    numFailed++;
  _ptrc_glDeleteProgram = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glDeleteProgram");
  if (!_ptrc_glDeleteProgram)
    numFailed++;
  _ptrc_glDeleteShader = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glDeleteShader");
  if (!_ptrc_glDeleteShader)
    numFailed++;
  _ptrc_glDetachShader = (void(CODEGEN_FUNCPTR*)(GLuint, GLuint))IntGetProcAddress("glDetachShader");
  if (!_ptrc_glDetachShader)
    numFailed++;
  _ptrc_glDisableVertexAttribArray = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glDisableVertexAttribArray");
  if (!_ptrc_glDisableVertexAttribArray)
    numFailed++;
  _ptrc_glDrawBuffers = (void(CODEGEN_FUNCPTR*)(GLsizei, const GLenum*))IntGetProcAddress("glDrawBuffers");
  if (!_ptrc_glDrawBuffers)
    numFailed++;
  _ptrc_glEnableVertexAttribArray = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glEnableVertexAttribArray");
  if (!_ptrc_glEnableVertexAttribArray)
    numFailed++;
  _ptrc_glGetActiveAttrib = (void(CODEGEN_FUNCPTR*)(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*,
                                                    GLchar*))IntGetProcAddress("glGetActiveAttrib");
  if (!_ptrc_glGetActiveAttrib)
    numFailed++;
  _ptrc_glGetActiveUniform = (void(CODEGEN_FUNCPTR*)(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*,
                                                     GLchar*))IntGetProcAddress("glGetActiveUniform");
  if (!_ptrc_glGetActiveUniform)
    numFailed++;
  _ptrc_glGetAttachedShaders =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLsizei, GLsizei*, GLuint*))IntGetProcAddress("glGetAttachedShaders");
  if (!_ptrc_glGetAttachedShaders)
    numFailed++;
  _ptrc_glGetAttribLocation = (GLint(CODEGEN_FUNCPTR*)(GLuint, const GLchar*))IntGetProcAddress("glGetAttribLocation");
  if (!_ptrc_glGetAttribLocation)
    numFailed++;
  _ptrc_glGetProgramInfoLog =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLsizei, GLsizei*, GLchar*))IntGetProcAddress("glGetProgramInfoLog");
  if (!_ptrc_glGetProgramInfoLog)
    numFailed++;
  _ptrc_glGetProgramiv = (void(CODEGEN_FUNCPTR*)(GLuint, GLenum, GLint*))IntGetProcAddress("glGetProgramiv");
  if (!_ptrc_glGetProgramiv)
    numFailed++;
  _ptrc_glGetShaderInfoLog =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLsizei, GLsizei*, GLchar*))IntGetProcAddress("glGetShaderInfoLog");
  if (!_ptrc_glGetShaderInfoLog)
    numFailed++;
  _ptrc_glGetShaderSource =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLsizei, GLsizei*, GLchar*))IntGetProcAddress("glGetShaderSource");
  if (!_ptrc_glGetShaderSource)
    numFailed++;
  _ptrc_glGetShaderiv = (void(CODEGEN_FUNCPTR*)(GLuint, GLenum, GLint*))IntGetProcAddress("glGetShaderiv");
  if (!_ptrc_glGetShaderiv)
    numFailed++;
  _ptrc_glGetUniformLocation =
      (GLint(CODEGEN_FUNCPTR*)(GLuint, const GLchar*))IntGetProcAddress("glGetUniformLocation");
  if (!_ptrc_glGetUniformLocation)
    numFailed++;
  _ptrc_glGetUniformfv = (void(CODEGEN_FUNCPTR*)(GLuint, GLint, GLfloat*))IntGetProcAddress("glGetUniformfv");
  if (!_ptrc_glGetUniformfv)
    numFailed++;
  _ptrc_glGetUniformiv = (void(CODEGEN_FUNCPTR*)(GLuint, GLint, GLint*))IntGetProcAddress("glGetUniformiv");
  if (!_ptrc_glGetUniformiv)
    numFailed++;
  _ptrc_glGetVertexAttribPointerv =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLenum, void**))IntGetProcAddress("glGetVertexAttribPointerv");
  if (!_ptrc_glGetVertexAttribPointerv)
    numFailed++;
  _ptrc_glGetVertexAttribdv =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLenum, GLdouble*))IntGetProcAddress("glGetVertexAttribdv");
  if (!_ptrc_glGetVertexAttribdv)
    numFailed++;
  _ptrc_glGetVertexAttribfv =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLenum, GLfloat*))IntGetProcAddress("glGetVertexAttribfv");
  if (!_ptrc_glGetVertexAttribfv)
    numFailed++;
  _ptrc_glGetVertexAttribiv = (void(CODEGEN_FUNCPTR*)(GLuint, GLenum, GLint*))IntGetProcAddress("glGetVertexAttribiv");
  if (!_ptrc_glGetVertexAttribiv)
    numFailed++;
  _ptrc_glIsProgram = (GLboolean(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glIsProgram");
  if (!_ptrc_glIsProgram)
    numFailed++;
  _ptrc_glIsShader = (GLboolean(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glIsShader");
  if (!_ptrc_glIsShader)
    numFailed++;
  _ptrc_glLinkProgram = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glLinkProgram");
  if (!_ptrc_glLinkProgram)
    numFailed++;
  _ptrc_glShaderSource =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLsizei, const GLchar* const*, const GLint*))IntGetProcAddress("glShaderSource");
  if (!_ptrc_glShaderSource)
    numFailed++;
  _ptrc_glStencilFuncSeparate =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint, GLuint))IntGetProcAddress("glStencilFuncSeparate");
  if (!_ptrc_glStencilFuncSeparate)
    numFailed++;
  _ptrc_glStencilMaskSeparate = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glStencilMaskSeparate");
  if (!_ptrc_glStencilMaskSeparate)
    numFailed++;
  _ptrc_glStencilOpSeparate =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLenum, GLenum))IntGetProcAddress("glStencilOpSeparate");
  if (!_ptrc_glStencilOpSeparate)
    numFailed++;
  _ptrc_glUniform1f = (void(CODEGEN_FUNCPTR*)(GLint, GLfloat))IntGetProcAddress("glUniform1f");
  if (!_ptrc_glUniform1f)
    numFailed++;
  _ptrc_glUniform1fv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLfloat*))IntGetProcAddress("glUniform1fv");
  if (!_ptrc_glUniform1fv)
    numFailed++;
  _ptrc_glUniform1i = (void(CODEGEN_FUNCPTR*)(GLint, GLint))IntGetProcAddress("glUniform1i");
  if (!_ptrc_glUniform1i)
    numFailed++;
  _ptrc_glUniform1iv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLint*))IntGetProcAddress("glUniform1iv");
  if (!_ptrc_glUniform1iv)
    numFailed++;
  _ptrc_glUniform2f = (void(CODEGEN_FUNCPTR*)(GLint, GLfloat, GLfloat))IntGetProcAddress("glUniform2f");
  if (!_ptrc_glUniform2f)
    numFailed++;
  _ptrc_glUniform2fv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLfloat*))IntGetProcAddress("glUniform2fv");
  if (!_ptrc_glUniform2fv)
    numFailed++;
  _ptrc_glUniform2i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint))IntGetProcAddress("glUniform2i");
  if (!_ptrc_glUniform2i)
    numFailed++;
  _ptrc_glUniform2iv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLint*))IntGetProcAddress("glUniform2iv");
  if (!_ptrc_glUniform2iv)
    numFailed++;
  _ptrc_glUniform3f = (void(CODEGEN_FUNCPTR*)(GLint, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glUniform3f");
  if (!_ptrc_glUniform3f)
    numFailed++;
  _ptrc_glUniform3fv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLfloat*))IntGetProcAddress("glUniform3fv");
  if (!_ptrc_glUniform3fv)
    numFailed++;
  _ptrc_glUniform3i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint, GLint))IntGetProcAddress("glUniform3i");
  if (!_ptrc_glUniform3i)
    numFailed++;
  _ptrc_glUniform3iv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLint*))IntGetProcAddress("glUniform3iv");
  if (!_ptrc_glUniform3iv)
    numFailed++;
  _ptrc_glUniform4f =
      (void(CODEGEN_FUNCPTR*)(GLint, GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glUniform4f");
  if (!_ptrc_glUniform4f)
    numFailed++;
  _ptrc_glUniform4fv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLfloat*))IntGetProcAddress("glUniform4fv");
  if (!_ptrc_glUniform4fv)
    numFailed++;
  _ptrc_glUniform4i = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint, GLint, GLint))IntGetProcAddress("glUniform4i");
  if (!_ptrc_glUniform4i)
    numFailed++;
  _ptrc_glUniform4iv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLint*))IntGetProcAddress("glUniform4iv");
  if (!_ptrc_glUniform4iv)
    numFailed++;
  _ptrc_glUniformMatrix2fv =
      (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, GLboolean, const GLfloat*))IntGetProcAddress("glUniformMatrix2fv");
  if (!_ptrc_glUniformMatrix2fv)
    numFailed++;
  _ptrc_glUniformMatrix3fv =
      (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, GLboolean, const GLfloat*))IntGetProcAddress("glUniformMatrix3fv");
  if (!_ptrc_glUniformMatrix3fv)
    numFailed++;
  _ptrc_glUniformMatrix4fv =
      (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, GLboolean, const GLfloat*))IntGetProcAddress("glUniformMatrix4fv");
  if (!_ptrc_glUniformMatrix4fv)
    numFailed++;
  _ptrc_glUseProgram = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glUseProgram");
  if (!_ptrc_glUseProgram)
    numFailed++;
  _ptrc_glValidateProgram = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glValidateProgram");
  if (!_ptrc_glValidateProgram)
    numFailed++;
  _ptrc_glVertexAttrib1d = (void(CODEGEN_FUNCPTR*)(GLuint, GLdouble))IntGetProcAddress("glVertexAttrib1d");
  if (!_ptrc_glVertexAttrib1d)
    numFailed++;
  _ptrc_glVertexAttrib1dv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLdouble*))IntGetProcAddress("glVertexAttrib1dv");
  if (!_ptrc_glVertexAttrib1dv)
    numFailed++;
  _ptrc_glVertexAttrib1f = (void(CODEGEN_FUNCPTR*)(GLuint, GLfloat))IntGetProcAddress("glVertexAttrib1f");
  if (!_ptrc_glVertexAttrib1f)
    numFailed++;
  _ptrc_glVertexAttrib1fv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLfloat*))IntGetProcAddress("glVertexAttrib1fv");
  if (!_ptrc_glVertexAttrib1fv)
    numFailed++;
  _ptrc_glVertexAttrib1s = (void(CODEGEN_FUNCPTR*)(GLuint, GLshort))IntGetProcAddress("glVertexAttrib1s");
  if (!_ptrc_glVertexAttrib1s)
    numFailed++;
  _ptrc_glVertexAttrib1sv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLshort*))IntGetProcAddress("glVertexAttrib1sv");
  if (!_ptrc_glVertexAttrib1sv)
    numFailed++;
  _ptrc_glVertexAttrib2d = (void(CODEGEN_FUNCPTR*)(GLuint, GLdouble, GLdouble))IntGetProcAddress("glVertexAttrib2d");
  if (!_ptrc_glVertexAttrib2d)
    numFailed++;
  _ptrc_glVertexAttrib2dv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLdouble*))IntGetProcAddress("glVertexAttrib2dv");
  if (!_ptrc_glVertexAttrib2dv)
    numFailed++;
  _ptrc_glVertexAttrib2f = (void(CODEGEN_FUNCPTR*)(GLuint, GLfloat, GLfloat))IntGetProcAddress("glVertexAttrib2f");
  if (!_ptrc_glVertexAttrib2f)
    numFailed++;
  _ptrc_glVertexAttrib2fv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLfloat*))IntGetProcAddress("glVertexAttrib2fv");
  if (!_ptrc_glVertexAttrib2fv)
    numFailed++;
  _ptrc_glVertexAttrib2s = (void(CODEGEN_FUNCPTR*)(GLuint, GLshort, GLshort))IntGetProcAddress("glVertexAttrib2s");
  if (!_ptrc_glVertexAttrib2s)
    numFailed++;
  _ptrc_glVertexAttrib2sv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLshort*))IntGetProcAddress("glVertexAttrib2sv");
  if (!_ptrc_glVertexAttrib2sv)
    numFailed++;
  _ptrc_glVertexAttrib3d =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glVertexAttrib3d");
  if (!_ptrc_glVertexAttrib3d)
    numFailed++;
  _ptrc_glVertexAttrib3dv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLdouble*))IntGetProcAddress("glVertexAttrib3dv");
  if (!_ptrc_glVertexAttrib3dv)
    numFailed++;
  _ptrc_glVertexAttrib3f =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glVertexAttrib3f");
  if (!_ptrc_glVertexAttrib3f)
    numFailed++;
  _ptrc_glVertexAttrib3fv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLfloat*))IntGetProcAddress("glVertexAttrib3fv");
  if (!_ptrc_glVertexAttrib3fv)
    numFailed++;
  _ptrc_glVertexAttrib3s =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLshort, GLshort, GLshort))IntGetProcAddress("glVertexAttrib3s");
  if (!_ptrc_glVertexAttrib3s)
    numFailed++;
  _ptrc_glVertexAttrib3sv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLshort*))IntGetProcAddress("glVertexAttrib3sv");
  if (!_ptrc_glVertexAttrib3sv)
    numFailed++;
  _ptrc_glVertexAttrib4Nbv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLbyte*))IntGetProcAddress("glVertexAttrib4Nbv");
  if (!_ptrc_glVertexAttrib4Nbv)
    numFailed++;
  _ptrc_glVertexAttrib4Niv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLint*))IntGetProcAddress("glVertexAttrib4Niv");
  if (!_ptrc_glVertexAttrib4Niv)
    numFailed++;
  _ptrc_glVertexAttrib4Nsv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLshort*))IntGetProcAddress("glVertexAttrib4Nsv");
  if (!_ptrc_glVertexAttrib4Nsv)
    numFailed++;
  _ptrc_glVertexAttrib4Nub =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte))IntGetProcAddress("glVertexAttrib4Nub");
  if (!_ptrc_glVertexAttrib4Nub)
    numFailed++;
  _ptrc_glVertexAttrib4Nubv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLubyte*))IntGetProcAddress("glVertexAttrib4Nubv");
  if (!_ptrc_glVertexAttrib4Nubv)
    numFailed++;
  _ptrc_glVertexAttrib4Nuiv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLuint*))IntGetProcAddress("glVertexAttrib4Nuiv");
  if (!_ptrc_glVertexAttrib4Nuiv)
    numFailed++;
  _ptrc_glVertexAttrib4Nusv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLushort*))IntGetProcAddress("glVertexAttrib4Nusv");
  if (!_ptrc_glVertexAttrib4Nusv)
    numFailed++;
  _ptrc_glVertexAttrib4bv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLbyte*))IntGetProcAddress("glVertexAttrib4bv");
  if (!_ptrc_glVertexAttrib4bv)
    numFailed++;
  _ptrc_glVertexAttrib4d =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble))IntGetProcAddress("glVertexAttrib4d");
  if (!_ptrc_glVertexAttrib4d)
    numFailed++;
  _ptrc_glVertexAttrib4dv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLdouble*))IntGetProcAddress("glVertexAttrib4dv");
  if (!_ptrc_glVertexAttrib4dv)
    numFailed++;
  _ptrc_glVertexAttrib4f =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat))IntGetProcAddress("glVertexAttrib4f");
  if (!_ptrc_glVertexAttrib4f)
    numFailed++;
  _ptrc_glVertexAttrib4fv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLfloat*))IntGetProcAddress("glVertexAttrib4fv");
  if (!_ptrc_glVertexAttrib4fv)
    numFailed++;
  _ptrc_glVertexAttrib4iv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLint*))IntGetProcAddress("glVertexAttrib4iv");
  if (!_ptrc_glVertexAttrib4iv)
    numFailed++;
  _ptrc_glVertexAttrib4s =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLshort, GLshort, GLshort, GLshort))IntGetProcAddress("glVertexAttrib4s");
  if (!_ptrc_glVertexAttrib4s)
    numFailed++;
  _ptrc_glVertexAttrib4sv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLshort*))IntGetProcAddress("glVertexAttrib4sv");
  if (!_ptrc_glVertexAttrib4sv)
    numFailed++;
  _ptrc_glVertexAttrib4ubv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLubyte*))IntGetProcAddress("glVertexAttrib4ubv");
  if (!_ptrc_glVertexAttrib4ubv)
    numFailed++;
  _ptrc_glVertexAttrib4uiv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLuint*))IntGetProcAddress("glVertexAttrib4uiv");
  if (!_ptrc_glVertexAttrib4uiv)
    numFailed++;
  _ptrc_glVertexAttrib4usv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLushort*))IntGetProcAddress("glVertexAttrib4usv");
  if (!_ptrc_glVertexAttrib4usv)
    numFailed++;
  _ptrc_glVertexAttribPointer = (void(CODEGEN_FUNCPTR*)(GLuint, GLint, GLenum, GLboolean, GLsizei,
                                                        const void*))IntGetProcAddress("glVertexAttribPointer");
  if (!_ptrc_glVertexAttribPointer)
    numFailed++;
  _ptrc_glUniformMatrix2x3fv =
      (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, GLboolean, const GLfloat*))IntGetProcAddress("glUniformMatrix2x3fv");
  if (!_ptrc_glUniformMatrix2x3fv)
    numFailed++;
  _ptrc_glUniformMatrix2x4fv =
      (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, GLboolean, const GLfloat*))IntGetProcAddress("glUniformMatrix2x4fv");
  if (!_ptrc_glUniformMatrix2x4fv)
    numFailed++;
  _ptrc_glUniformMatrix3x2fv =
      (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, GLboolean, const GLfloat*))IntGetProcAddress("glUniformMatrix3x2fv");
  if (!_ptrc_glUniformMatrix3x2fv)
    numFailed++;
  _ptrc_glUniformMatrix3x4fv =
      (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, GLboolean, const GLfloat*))IntGetProcAddress("glUniformMatrix3x4fv");
  if (!_ptrc_glUniformMatrix3x4fv)
    numFailed++;
  _ptrc_glUniformMatrix4x2fv =
      (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, GLboolean, const GLfloat*))IntGetProcAddress("glUniformMatrix4x2fv");
  if (!_ptrc_glUniformMatrix4x2fv)
    numFailed++;
  _ptrc_glUniformMatrix4x3fv =
      (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, GLboolean, const GLfloat*))IntGetProcAddress("glUniformMatrix4x3fv");
  if (!_ptrc_glUniformMatrix4x3fv)
    numFailed++;
  _ptrc_glBeginConditionalRender =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLenum))IntGetProcAddress("glBeginConditionalRender");
  if (!_ptrc_glBeginConditionalRender)
    numFailed++;
  _ptrc_glBeginTransformFeedback = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glBeginTransformFeedback");
  if (!_ptrc_glBeginTransformFeedback)
    numFailed++;
  _ptrc_glBindBufferBase = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint, GLuint))IntGetProcAddress("glBindBufferBase");
  if (!_ptrc_glBindBufferBase)
    numFailed++;
  _ptrc_glBindBufferRange =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr))IntGetProcAddress("glBindBufferRange");
  if (!_ptrc_glBindBufferRange)
    numFailed++;
  _ptrc_glBindFragDataLocation =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLuint, const GLchar*))IntGetProcAddress("glBindFragDataLocation");
  if (!_ptrc_glBindFragDataLocation)
    numFailed++;
  _ptrc_glBindFramebuffer = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glBindFramebuffer");
  if (!_ptrc_glBindFramebuffer)
    numFailed++;
  _ptrc_glBindRenderbuffer = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glBindRenderbuffer");
  if (!_ptrc_glBindRenderbuffer)
    numFailed++;
  _ptrc_glBindVertexArray = (void(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glBindVertexArray");
  if (!_ptrc_glBindVertexArray)
    numFailed++;
  _ptrc_glBlitFramebuffer = (void(CODEGEN_FUNCPTR*)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield,
                                                    GLenum))IntGetProcAddress("glBlitFramebuffer");
  if (!_ptrc_glBlitFramebuffer)
    numFailed++;
  _ptrc_glCheckFramebufferStatus = (GLenum(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glCheckFramebufferStatus");
  if (!_ptrc_glCheckFramebufferStatus)
    numFailed++;
  _ptrc_glClampColor = (void(CODEGEN_FUNCPTR*)(GLenum, GLenum))IntGetProcAddress("glClampColor");
  if (!_ptrc_glClampColor)
    numFailed++;
  _ptrc_glClearBufferfi = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, GLfloat, GLint))IntGetProcAddress("glClearBufferfi");
  if (!_ptrc_glClearBufferfi)
    numFailed++;
  _ptrc_glClearBufferfv = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, const GLfloat*))IntGetProcAddress("glClearBufferfv");
  if (!_ptrc_glClearBufferfv)
    numFailed++;
  _ptrc_glClearBufferiv = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, const GLint*))IntGetProcAddress("glClearBufferiv");
  if (!_ptrc_glClearBufferiv)
    numFailed++;
  _ptrc_glClearBufferuiv = (void(CODEGEN_FUNCPTR*)(GLenum, GLint, const GLuint*))IntGetProcAddress("glClearBufferuiv");
  if (!_ptrc_glClearBufferuiv)
    numFailed++;
  _ptrc_glColorMaski =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean))IntGetProcAddress("glColorMaski");
  if (!_ptrc_glColorMaski)
    numFailed++;
  _ptrc_glDeleteFramebuffers =
      (void(CODEGEN_FUNCPTR*)(GLsizei, const GLuint*))IntGetProcAddress("glDeleteFramebuffers");
  if (!_ptrc_glDeleteFramebuffers)
    numFailed++;
  _ptrc_glDeleteRenderbuffers =
      (void(CODEGEN_FUNCPTR*)(GLsizei, const GLuint*))IntGetProcAddress("glDeleteRenderbuffers");
  if (!_ptrc_glDeleteRenderbuffers)
    numFailed++;
  _ptrc_glDeleteVertexArrays =
      (void(CODEGEN_FUNCPTR*)(GLsizei, const GLuint*))IntGetProcAddress("glDeleteVertexArrays");
  if (!_ptrc_glDeleteVertexArrays)
    numFailed++;
  _ptrc_glDisablei = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glDisablei");
  if (!_ptrc_glDisablei)
    numFailed++;
  _ptrc_glEnablei = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glEnablei");
  if (!_ptrc_glEnablei)
    numFailed++;
  _ptrc_glEndConditionalRender = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glEndConditionalRender");
  if (!_ptrc_glEndConditionalRender)
    numFailed++;
  _ptrc_glEndTransformFeedback = (void(CODEGEN_FUNCPTR*)(void))IntGetProcAddress("glEndTransformFeedback");
  if (!_ptrc_glEndTransformFeedback)
    numFailed++;
  _ptrc_glFlushMappedBufferRange =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLintptr, GLsizeiptr))IntGetProcAddress("glFlushMappedBufferRange");
  if (!_ptrc_glFlushMappedBufferRange)
    numFailed++;
  _ptrc_glFramebufferRenderbuffer =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLenum, GLuint))IntGetProcAddress("glFramebufferRenderbuffer");
  if (!_ptrc_glFramebufferRenderbuffer)
    numFailed++;
  _ptrc_glFramebufferTexture1D =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLenum, GLuint, GLint))IntGetProcAddress("glFramebufferTexture1D");
  if (!_ptrc_glFramebufferTexture1D)
    numFailed++;
  _ptrc_glFramebufferTexture2D =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLenum, GLuint, GLint))IntGetProcAddress("glFramebufferTexture2D");
  if (!_ptrc_glFramebufferTexture2D)
    numFailed++;
  _ptrc_glFramebufferTexture3D =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLenum, GLuint, GLint, GLint))IntGetProcAddress("glFramebufferTexture3D");
  if (!_ptrc_glFramebufferTexture3D)
    numFailed++;
  _ptrc_glFramebufferTextureLayer =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLuint, GLint, GLint))IntGetProcAddress("glFramebufferTextureLayer");
  if (!_ptrc_glFramebufferTextureLayer)
    numFailed++;
  _ptrc_glGenFramebuffers = (void(CODEGEN_FUNCPTR*)(GLsizei, GLuint*))IntGetProcAddress("glGenFramebuffers");
  if (!_ptrc_glGenFramebuffers)
    numFailed++;
  _ptrc_glGenRenderbuffers = (void(CODEGEN_FUNCPTR*)(GLsizei, GLuint*))IntGetProcAddress("glGenRenderbuffers");
  if (!_ptrc_glGenRenderbuffers)
    numFailed++;
  _ptrc_glGenVertexArrays = (void(CODEGEN_FUNCPTR*)(GLsizei, GLuint*))IntGetProcAddress("glGenVertexArrays");
  if (!_ptrc_glGenVertexArrays)
    numFailed++;
  _ptrc_glGenerateMipmap = (void(CODEGEN_FUNCPTR*)(GLenum))IntGetProcAddress("glGenerateMipmap");
  if (!_ptrc_glGenerateMipmap)
    numFailed++;
  _ptrc_glGetBooleani_v = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint, GLboolean*))IntGetProcAddress("glGetBooleani_v");
  if (!_ptrc_glGetBooleani_v)
    numFailed++;
  _ptrc_glGetFragDataLocation =
      (GLint(CODEGEN_FUNCPTR*)(GLuint, const GLchar*))IntGetProcAddress("glGetFragDataLocation");
  if (!_ptrc_glGetFragDataLocation)
    numFailed++;
  _ptrc_glGetFramebufferAttachmentParameteriv = (void(CODEGEN_FUNCPTR*)(
      GLenum, GLenum, GLenum, GLint*))IntGetProcAddress("glGetFramebufferAttachmentParameteriv");
  if (!_ptrc_glGetFramebufferAttachmentParameteriv)
    numFailed++;
  _ptrc_glGetIntegeri_v = (void(CODEGEN_FUNCPTR*)(GLenum, GLuint, GLint*))IntGetProcAddress("glGetIntegeri_v");
  if (!_ptrc_glGetIntegeri_v)
    numFailed++;
  _ptrc_glGetRenderbufferParameteriv =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint*))IntGetProcAddress("glGetRenderbufferParameteriv");
  if (!_ptrc_glGetRenderbufferParameteriv)
    numFailed++;
  _ptrc_glGetStringi = (const GLubyte*(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glGetStringi");
  if (!_ptrc_glGetStringi)
    numFailed++;
  _ptrc_glGetTexParameterIiv =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLint*))IntGetProcAddress("glGetTexParameterIiv");
  if (!_ptrc_glGetTexParameterIiv)
    numFailed++;
  _ptrc_glGetTexParameterIuiv =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLuint*))IntGetProcAddress("glGetTexParameterIuiv");
  if (!_ptrc_glGetTexParameterIuiv)
    numFailed++;
  _ptrc_glGetTransformFeedbackVarying = (void(CODEGEN_FUNCPTR*)(
      GLuint, GLuint, GLsizei, GLsizei*, GLsizei*, GLenum*, GLchar*))IntGetProcAddress("glGetTransformFeedbackVarying");
  if (!_ptrc_glGetTransformFeedbackVarying)
    numFailed++;
  _ptrc_glGetUniformuiv = (void(CODEGEN_FUNCPTR*)(GLuint, GLint, GLuint*))IntGetProcAddress("glGetUniformuiv");
  if (!_ptrc_glGetUniformuiv)
    numFailed++;
  _ptrc_glGetVertexAttribIiv =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLenum, GLint*))IntGetProcAddress("glGetVertexAttribIiv");
  if (!_ptrc_glGetVertexAttribIiv)
    numFailed++;
  _ptrc_glGetVertexAttribIuiv =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLenum, GLuint*))IntGetProcAddress("glGetVertexAttribIuiv");
  if (!_ptrc_glGetVertexAttribIuiv)
    numFailed++;
  _ptrc_glIsEnabledi = (GLboolean(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glIsEnabledi");
  if (!_ptrc_glIsEnabledi)
    numFailed++;
  _ptrc_glIsFramebuffer = (GLboolean(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glIsFramebuffer");
  if (!_ptrc_glIsFramebuffer)
    numFailed++;
  _ptrc_glIsRenderbuffer = (GLboolean(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glIsRenderbuffer");
  if (!_ptrc_glIsRenderbuffer)
    numFailed++;
  _ptrc_glIsVertexArray = (GLboolean(CODEGEN_FUNCPTR*)(GLuint))IntGetProcAddress("glIsVertexArray");
  if (!_ptrc_glIsVertexArray)
    numFailed++;
  _ptrc_glMapBufferRange =
      (void*(CODEGEN_FUNCPTR*)(GLenum, GLintptr, GLsizeiptr, GLbitfield))IntGetProcAddress("glMapBufferRange");
  if (!_ptrc_glMapBufferRange)
    numFailed++;
  _ptrc_glRenderbufferStorage =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, GLsizei, GLsizei))IntGetProcAddress("glRenderbufferStorage");
  if (!_ptrc_glRenderbufferStorage)
    numFailed++;
  _ptrc_glRenderbufferStorageMultisample = (void(CODEGEN_FUNCPTR*)(
      GLenum, GLsizei, GLenum, GLsizei, GLsizei))IntGetProcAddress("glRenderbufferStorageMultisample");
  if (!_ptrc_glRenderbufferStorageMultisample)
    numFailed++;
  _ptrc_glTexParameterIiv =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLint*))IntGetProcAddress("glTexParameterIiv");
  if (!_ptrc_glTexParameterIiv)
    numFailed++;
  _ptrc_glTexParameterIuiv =
      (void(CODEGEN_FUNCPTR*)(GLenum, GLenum, const GLuint*))IntGetProcAddress("glTexParameterIuiv");
  if (!_ptrc_glTexParameterIuiv)
    numFailed++;
  _ptrc_glTransformFeedbackVaryings = (void(CODEGEN_FUNCPTR*)(GLuint, GLsizei, const GLchar* const*,
                                                              GLenum))IntGetProcAddress("glTransformFeedbackVaryings");
  if (!_ptrc_glTransformFeedbackVaryings)
    numFailed++;
  _ptrc_glUniform1ui = (void(CODEGEN_FUNCPTR*)(GLint, GLuint))IntGetProcAddress("glUniform1ui");
  if (!_ptrc_glUniform1ui)
    numFailed++;
  _ptrc_glUniform1uiv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLuint*))IntGetProcAddress("glUniform1uiv");
  if (!_ptrc_glUniform1uiv)
    numFailed++;
  _ptrc_glUniform2ui = (void(CODEGEN_FUNCPTR*)(GLint, GLuint, GLuint))IntGetProcAddress("glUniform2ui");
  if (!_ptrc_glUniform2ui)
    numFailed++;
  _ptrc_glUniform2uiv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLuint*))IntGetProcAddress("glUniform2uiv");
  if (!_ptrc_glUniform2uiv)
    numFailed++;
  _ptrc_glUniform3ui = (void(CODEGEN_FUNCPTR*)(GLint, GLuint, GLuint, GLuint))IntGetProcAddress("glUniform3ui");
  if (!_ptrc_glUniform3ui)
    numFailed++;
  _ptrc_glUniform3uiv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLuint*))IntGetProcAddress("glUniform3uiv");
  if (!_ptrc_glUniform3uiv)
    numFailed++;
  _ptrc_glUniform4ui = (void(CODEGEN_FUNCPTR*)(GLint, GLuint, GLuint, GLuint, GLuint))IntGetProcAddress("glUniform4ui");
  if (!_ptrc_glUniform4ui)
    numFailed++;
  _ptrc_glUniform4uiv = (void(CODEGEN_FUNCPTR*)(GLint, GLsizei, const GLuint*))IntGetProcAddress("glUniform4uiv");
  if (!_ptrc_glUniform4uiv)
    numFailed++;
  _ptrc_glVertexAttribI1i = (void(CODEGEN_FUNCPTR*)(GLuint, GLint))IntGetProcAddress("glVertexAttribI1i");
  if (!_ptrc_glVertexAttribI1i)
    numFailed++;
  _ptrc_glVertexAttribI1iv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLint*))IntGetProcAddress("glVertexAttribI1iv");
  if (!_ptrc_glVertexAttribI1iv)
    numFailed++;
  _ptrc_glVertexAttribI1ui = (void(CODEGEN_FUNCPTR*)(GLuint, GLuint))IntGetProcAddress("glVertexAttribI1ui");
  if (!_ptrc_glVertexAttribI1ui)
    numFailed++;
  _ptrc_glVertexAttribI1uiv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLuint*))IntGetProcAddress("glVertexAttribI1uiv");
  if (!_ptrc_glVertexAttribI1uiv)
    numFailed++;
  _ptrc_glVertexAttribI2i = (void(CODEGEN_FUNCPTR*)(GLuint, GLint, GLint))IntGetProcAddress("glVertexAttribI2i");
  if (!_ptrc_glVertexAttribI2i)
    numFailed++;
  _ptrc_glVertexAttribI2iv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLint*))IntGetProcAddress("glVertexAttribI2iv");
  if (!_ptrc_glVertexAttribI2iv)
    numFailed++;
  _ptrc_glVertexAttribI2ui = (void(CODEGEN_FUNCPTR*)(GLuint, GLuint, GLuint))IntGetProcAddress("glVertexAttribI2ui");
  if (!_ptrc_glVertexAttribI2ui)
    numFailed++;
  _ptrc_glVertexAttribI2uiv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLuint*))IntGetProcAddress("glVertexAttribI2uiv");
  if (!_ptrc_glVertexAttribI2uiv)
    numFailed++;
  _ptrc_glVertexAttribI3i = (void(CODEGEN_FUNCPTR*)(GLuint, GLint, GLint, GLint))IntGetProcAddress("glVertexAttribI3i");
  if (!_ptrc_glVertexAttribI3i)
    numFailed++;
  _ptrc_glVertexAttribI3iv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLint*))IntGetProcAddress("glVertexAttribI3iv");
  if (!_ptrc_glVertexAttribI3iv)
    numFailed++;
  _ptrc_glVertexAttribI3ui =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLuint, GLuint, GLuint))IntGetProcAddress("glVertexAttribI3ui");
  if (!_ptrc_glVertexAttribI3ui)
    numFailed++;
  _ptrc_glVertexAttribI3uiv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLuint*))IntGetProcAddress("glVertexAttribI3uiv");
  if (!_ptrc_glVertexAttribI3uiv)
    numFailed++;
  _ptrc_glVertexAttribI4bv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLbyte*))IntGetProcAddress("glVertexAttribI4bv");
  if (!_ptrc_glVertexAttribI4bv)
    numFailed++;
  _ptrc_glVertexAttribI4i =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLint, GLint, GLint, GLint))IntGetProcAddress("glVertexAttribI4i");
  if (!_ptrc_glVertexAttribI4i)
    numFailed++;
  _ptrc_glVertexAttribI4iv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLint*))IntGetProcAddress("glVertexAttribI4iv");
  if (!_ptrc_glVertexAttribI4iv)
    numFailed++;
  _ptrc_glVertexAttribI4sv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLshort*))IntGetProcAddress("glVertexAttribI4sv");
  if (!_ptrc_glVertexAttribI4sv)
    numFailed++;
  _ptrc_glVertexAttribI4ubv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLubyte*))IntGetProcAddress("glVertexAttribI4ubv");
  if (!_ptrc_glVertexAttribI4ubv)
    numFailed++;
  _ptrc_glVertexAttribI4ui =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLuint, GLuint, GLuint, GLuint))IntGetProcAddress("glVertexAttribI4ui");
  if (!_ptrc_glVertexAttribI4ui)
    numFailed++;
  _ptrc_glVertexAttribI4uiv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLuint*))IntGetProcAddress("glVertexAttribI4uiv");
  if (!_ptrc_glVertexAttribI4uiv)
    numFailed++;
  _ptrc_glVertexAttribI4usv = (void(CODEGEN_FUNCPTR*)(GLuint, const GLushort*))IntGetProcAddress("glVertexAttribI4usv");
  if (!_ptrc_glVertexAttribI4usv)
    numFailed++;
  _ptrc_glVertexAttribIPointer =
      (void(CODEGEN_FUNCPTR*)(GLuint, GLint, GLenum, GLsizei, const void*))IntGetProcAddress("glVertexAttribIPointer");
  if (!_ptrc_glVertexAttribIPointer)
    numFailed++;
  return numFailed;
}

typedef int (*PFN_LOADFUNCPOINTERS)(void);
typedef struct ogl_StrToExtMap_s
{
  char* extensionName;
  int* extensionVariable;
  PFN_LOADFUNCPOINTERS LoadExtension;
} ogl_StrToExtMap;

static ogl_StrToExtMap ExtensionMap[1] = {
    {"", NULL, NULL},
};

static int g_extensionMapSize = 0;

static ogl_StrToExtMap* FindExtEntry(const char* extensionName)
{
  int loop;
  ogl_StrToExtMap* currLoc = ExtensionMap;
  for (loop = 0; loop < g_extensionMapSize; ++loop, ++currLoc)
  {
    if (strcmp(extensionName, currLoc->extensionName) == 0)
      return currLoc;
  }

  return NULL;
}

static void ClearExtensionVars(void)
{
}

static void LoadExtByName(const char* extensionName)
{
  ogl_StrToExtMap* entry = NULL;
  entry = FindExtEntry(extensionName);
  if (entry)
  {
    if (entry->LoadExtension)
    {
      int numFailed = entry->LoadExtension();
      if (numFailed == 0)
      {
        *(entry->extensionVariable) = ogl_LOAD_SUCCEEDED;
      }
      else
      {
        *(entry->extensionVariable) = ogl_LOAD_SUCCEEDED + numFailed;
      }
    }
    else
    {
      *(entry->extensionVariable) = ogl_LOAD_SUCCEEDED;
    }
  }
}

static void ProcExtsFromExtList(void)
{
  GLint iLoop;
  GLint iNumExtensions = 0;
  _ptrc_glGetIntegerv(GL_NUM_EXTENSIONS, &iNumExtensions);

  for (iLoop = 0; iLoop < iNumExtensions; iLoop++)
  {
    const char* strExtensionName = (const char*)_ptrc_glGetStringi(GL_EXTENSIONS, iLoop);
    LoadExtByName(strExtensionName);
  }
}

int ogl_LoadFunctions()
{
  int numFailed = 0;
  ClearExtensionVars();

  _ptrc_glGetIntegerv = (void(CODEGEN_FUNCPTR*)(GLenum, GLint*))IntGetProcAddress("glGetIntegerv");
  if (!_ptrc_glGetIntegerv)
    return ogl_LOAD_FAILED;
  _ptrc_glGetStringi = (const GLubyte*(CODEGEN_FUNCPTR*)(GLenum, GLuint))IntGetProcAddress("glGetStringi");
  if (!_ptrc_glGetStringi)
    return ogl_LOAD_FAILED;

  ProcExtsFromExtList();
  numFailed = Load_Version_3_0();

  if (numFailed == 0)
    return ogl_LOAD_SUCCEEDED;
  else
    return ogl_LOAD_SUCCEEDED + numFailed;
}

static int g_major_version = 0;
static int g_minor_version = 0;

static void GetGLVersion(void)
{
  glGetIntegerv(GL_MAJOR_VERSION, &g_major_version);
  glGetIntegerv(GL_MINOR_VERSION, &g_minor_version);
}

int ogl_GetMajorVersion(void)
{
  if (g_major_version == 0)
    GetGLVersion();
  return g_major_version;
}

int ogl_GetMinorVersion(void)
{
  if (g_major_version == 0) /*Yes, check the major version to get the minor one.*/
    GetGLVersion();
  return g_minor_version;
}

int ogl_IsVersionGEQ(int majorVersion, int minorVersion)
{
  if (g_major_version == 0)
    GetGLVersion();

  if (majorVersion < g_major_version)
    return 1;
  if (majorVersion > g_major_version)
    return 0;
  if (minorVersion <= g_minor_version)
    return 1;
  return 0;
}
