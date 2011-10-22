#include "itl-gobject.h"

/**
 * itl_h_date:
 *
 * @day: (in): Gregorian day
 * @month: (in): Gregorian month
 * @year: (in): Gregorian year
 * 
 * Convert Gregorian date to Hijra date
 *
 * Return value: (transfer full): Hijri date
 */
GDate *itl_h_date(gint day, gint month, gint year) {
  sDate ITLDate;
  GDate *cdate;
  int ret;

  ret = h_date(&ITLDate, (int) day, (int) month, (int) year);

  cdate = g_date_new_dmy(ITLDate.day, ITLDate.month, ITLDate.year);

  return(cdate);
}

/**
 * itl_h_date:
 *
 * @day: (in): Hijri day
 * @month: (in): Hijri month
 * @year: (in): Hijri year
 * 
 * Convert Hijri date to Gregorian date
 *
 * Return value: (transfer full): Gregorian date
 */
GDate *itl_g_date(gint day, gint month, gint year) {
  sDate ITLDate;
  GDate *cdate;
  int ret;

  ret = g_date(&ITLDate, (int) day, (int) month, (int) year);

  cdate = g_date_new_dmy(ITLDate.day, ITLDate.month, ITLDate.year);

  return(cdate);
}

/**
 * itl_h_date:
 *
 * @dg: (in): Gregorian day
 * @mg: (in): Gregorian month
 * @yg: (in): Gregorian year
 * 
 * Convert Gregorian date to Hijra date using Umm Ul-Qura algorithm
 *
 * Return value: (transfer full): Hijri date
 */
GDate *itl_G2H(gint yg, gint mg, gint dg) {
  sDate ITLDate;
  GDate *cdate;
  int ret;

  ret = G2H(&ITLDate, (int) yg, (int) mg, (int) dg);

  cdate = g_date_new_dmy(ITLDate.day, ITLDate.month, ITLDate.year);

  return(cdate);
}

/**
 * itl_h_date:
 *
 * @dh: (in): Hijri day
 * @mh: (in): Hijri month
 * @yh: (in): Hijri year
 * 
 * Convert Hijri date to Gregorian date using Umm Ul-Qura algorithm
 *
 * Return value: (transfer full): Gregorian date
 */
GDate *itl_H2G(gint yh, gint mh, gint dh) {
  sDate ITLDate;
  GDate *cdate;
  int ret;

  ret = H2G(&ITLDate, (int) yh, (int) mh, (int) dh);

  cdate = g_date_new_dmy(ITLDate.day, ITLDate.month, ITLDate.year);

  return(cdate);
}

gint itl_HijriGreg (GDate *HijriDate, GDate *GregDate, gboolean Hijri, gboolean UmmAlQura) {
  sDate ITLDate;
  int ret;

  if(Hijri) {
    if(UmmAlQura) {
      ret = H2G(&ITLDate, (int) GregDate->day, (int) GregDate->month, (int)
                GregDate->year);
    }
    else {
      ret = h_date(&ITLDate, (int) GregDate->day, (int) GregDate->month, (int)
                   GregDate->year);
    }

    HijriDate->julian = 0;
    HijriDate->dmy = 1;
    HijriDate->day = ITLDate.day;
    HijriDate->month = ITLDate.month;
    HijriDate->year = ITLDate.year;
  }
  else {
    if(UmmAlQura) {
      ret = G2H(&ITLDate, (int) HijriDate->day, (int) HijriDate->month, (int)
                HijriDate->year);
    }
    else {
      ret = g_date(&ITLDate, (int) HijriDate->day, (int) HijriDate->month, (int)
                   HijriDate->year);
    }

    GregDate->julian = 0;
    GregDate->dmy = 1;
    GregDate->day = ITLDate.day;
    GregDate->month = ITLDate.month;
    GregDate->year = ITLDate.year;
  }

  return((gint) ret);
}

G_DEFINE_TYPE (ItlPrayer, itl_prayer, G_TYPE_OBJECT);
#define ITL_PRAYER_GET_PRIVATE(obj) \
(G_TYPE_INSTANCE_GET_PRIVATE ((obj), ITL_TYPE_PRAYER, ItlPrayerPrivate))

struct _ItlPrayerPrivate
{
  Method method;
  Location loc;
  Prayer prayer[6];
};

static void
itl_prayer_class_init (ItlPrayerClass *klass)
{
  GObjectClass        *gobject_class = G_OBJECT_CLASS (klass);

  g_type_class_add_private (gobject_class, sizeof (ItlPrayerPrivate));
}

static void
itl_prayer_init (ItlPrayer *self)
{
  ItlPrayerPrivate *priv;

  self->priv = priv = ITL_PRAYER_GET_PRIVATE (self);
}

GObject*
itl_prayer_new (void)
{
  return g_object_new (ITL_TYPE_PRAYER, NULL);
}

void
itl_prayer_getMethod (ItlPrayer *prayer, gint n)
{
  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  getMethod((int) n, &prayer->priv->method);

  g_object_unref (prayer);
}

void
itl_prayer_getPrayerTimes (ItlPrayer *prayer, GDate *cdate)
{
  Date ITLDate;

  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  ITLDate.day = cdate->day;
  ITLDate.month = cdate->month;
  ITLDate.year = cdate->year;

  getPrayerTimes (&prayer->priv->loc, &prayer->priv->method, &ITLDate,
                  &prayer->priv->prayer);

  g_object_unref (prayer);
}

void
itl_prayer_getNextDayFajr (ItlPrayer *prayer, GDate *cdate)
{
  Date ITLDate;

  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  ITLDate.day = cdate->day;
  ITLDate.month = cdate->month;
  ITLDate.year = cdate->year;

  getNextDayFajr (&prayer->priv->loc, &prayer->priv->method, &ITLDate,
                  &prayer->priv->prayer);

  g_object_unref (prayer);
}

gdouble
itl_prayer_getNorthQibla (ItlPrayer *prayer)
{
  gdouble NorthQibla;

  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  NorthQibla = (gdouble) getNorthQibla (&prayer->priv->loc);

  g_object_unref (prayer);

  return(NorthQibla);
}

void
itl_prayer_setLocation (ItlPrayer *prayer, gdouble degreeLong, gdouble
                        degreeLat, gdouble gmtDiff, gboolean dst, gdouble
                        seaLevel, gdouble pressure, gdouble temperature)
{
  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  prayer->priv->loc.degreeLong  = (double) degreeLong;
  prayer->priv->loc.degreeLat   = (double) degreeLat;
  prayer->priv->loc.gmtDiff     = (double) gmtDiff;
  prayer->priv->loc.dst         = (int) dst;
  prayer->priv->loc.seaLevel    = (double) seaLevel;
  prayer->priv->loc.pressure    = (double) pressure;
  prayer->priv->loc.temperature = (double) temperature;

  g_object_unref (prayer);
}
