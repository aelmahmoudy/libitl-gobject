#ifndef _ITL_GOBJECT_H
#define _ITL_GOBJECT_H

#include <hijri.h>
#include <prayer.h>
#include <glib.h>
#include <glib-object.h>

GDate *itl_h_date(gint day, gint month, gint year);
GDate *itl_g_date(gint day, gint month, gint year);

GDate *itl_G2H(gint yg, gint mg, gint dg);
GDate *itl_H2G(gint yh, gint mh, gint dh);

gint itl_HijriGreg (GDate *HijriDate, GDate *GregDate, gboolean Hijri, gboolean UmmAlQura);

G_BEGIN_DECLS

#define ITL_TYPE_PRAYER tut_triangle_get_type()

#define ITL_PRAYER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  ITL_TYPE_PRAYER, TutTriangle))

#define ITL_PRAYER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  ITL_TYPE_PRAYER, TutTriangleClass))

#define GOBJECT_IS_PRAYER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  ITL_TYPE_PRAYER))

#define GOBJECT_IS_PRAYER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  ITL_TYPE_PRAYER))

#define ITL_PRAYER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  ITL_TYPE_PRAYER, TutTriangleClass))

typedef struct _ItlPrayer ItlPrayer;
typedef struct _ItlPrayerClass ItlPrayerClass;
typedef struct _ItlPrayerPrivate ItlPrayerPrivate;

struct _ItlPrayer {
  GObject parent;

  /* private */
  ItlPrayerPrivate *priv;
};

struct _ItlPrayerClass 
{
  GObjectClass parent_class;
};

//GType itl_prayer_get_type (void) G_GNUC_CONST;
GObject *itl_prayer_new              (void);

void itl_prayer_getMethod(ItlPrayer *prayer, gint n);
void itl_prayer_getPrayerTimes (ItlPrayer *prayer, GDate *cday);
void itl_prayer_getNextDayFajr (ItlPrayer *prayer, GDate *cday);
gdouble itl_prayer_getNorthQibla(ItlPrayer *prayer);

G_END_DECLS


#endif // _ITL_GOBJECT_H
