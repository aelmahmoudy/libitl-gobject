/* Copyright (C) 2011 أحمد المحمودي (Ahmed El-Mahmoudy) <aelmahmoudy@sabily.org>

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 3, or (at your option) any later
   version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along with
   this program. If not, see <http://www.gnu.org/licenses/>.
*/
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

GDate *itl_HijriGreg (GDate *DateIn, gboolean Hijri, gboolean UmmAlQura);

G_BEGIN_DECLS

typedef enum
{
  SHAFII = 1,
  HANAFI = 2
} ItlMathhab;

typedef enum
{
  NOROUND = 0,
  NORMAL = 1,
  SPECIAL = 2,
  AGGRESSIVE = 3
} ItlRoundMethod;

typedef enum
{
  DEFAULT = 0,
  EGYPTIAN = 1,
  KARACHI_SHAFII = 2,
  KARACHI_HANAFI = 3,
  ISNA = 4,
  MWL = 5,
  UMM_AL_QURA = 6,
  FIXED_ISHA = 7,
  EGYPTIAN_EG = 8
} ItlMethod;

typedef enum
{
  NONE = 0,
  NEAREST_LAT_ALL = 1,
  NEAREST_LAT_ALWAYS = 2,
  NEAREST_LAT_INVALID = 3,
  NEAREST_GOOD_DAY_ALWAYS = 4,
  NEAREST_GOOD_DAY_INVALID = 5,
  ONE_SEVENTH_NIGHT_ALWAYS = 6,
  ONE_SEVENTH_NIGHT_INVALID = 7,
  ONE_SEVENTH_DAY_ALWAYS = 8,
  ONE_SEVENTH_DAY_INVALID = 9,
  HALF_NIGHT_ALWAYS = 10,
  HALF_NIGHT_INVALID = 11,
  MINS_FROM_ALWAYS = 12,
  MINS_FROM_INVALID = 13
} ItlExtremeMethod;

#define ITL_TYPE_PRAYER itl_prayer_get_type()

#define ITL_PRAYER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
  ITL_TYPE_PRAYER, ItlPrayer))

#define ITL_PRAYER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
  ITL_TYPE_PRAYER, ItlPrayerClass))

#define GOBJECT_IS_PRAYER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
  ITL_TYPE_PRAYER))

#define GOBJECT_IS_PRAYER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
  ITL_TYPE_PRAYER))

#define ITL_PRAYER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
  ITL_TYPE_PRAYER, ItlPrayerClass))

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

GType itl_prayer_get_type (void) G_GNUC_CONST;
ItlPrayer *itl_prayer_new              (void);

void itl_prayer_setMethod(ItlPrayer *prayer, ItlMethod n);
GList *itl_prayer_getPrayerTimes (ItlPrayer *prayer, GDate *cdate);
GDateTime *itl_prayer_getNextDayFajr (ItlPrayer *prayer, GDate *cdate);
gdouble itl_prayer_getNorthQibla(ItlPrayer *prayer);
void itl_prayer_setLocation (ItlPrayer *prayer, gdouble degreeLong, gdouble
                             degreeLat, gdouble gmtDiff, gboolean dst);

G_END_DECLS


#endif // _ITL_GOBJECT_H
