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
 * itl_g_date:
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
 * itl_G2H:
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
 * itl_H2G:
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

/**
 * itl_HijriGreg:
 *
 * @DateIn: (in): Date struct to convert
 * @Hijri: (in): DateIn date type; TRUE=Hijri, FALSE=Gregorian
 * @UmmAlQura: (in): TRUE=Use Umm Al-Qura algorithm, FALSE=otherwise
 *
 * Convert Hijri date to Gregorian date using Umm Ul-Qura algorithm
 *
 * Return value: (transfer full): Converted Date struct
 */
GDate *itl_HijriGreg (GDate *DateIn, gboolean Hijri, gboolean UmmAlQura) {
  sDate ITLDate;
  GDate *cdate;
  int ret;

  if(Hijri) {
    if(UmmAlQura) {
      ret = H2G(&ITLDate, (int) g_date_get_day(DateIn), (int) g_date_get_month(DateIn), (int)
                g_date_get_year(DateIn));
    }
    else {
      ret = h_date(&ITLDate, (int) g_date_get_day(DateIn), (int) g_date_get_month(DateIn), (int)
                   g_date_get_year(DateIn));
    }
  }
  else {
    if(UmmAlQura) {
      ret = G2H(&ITLDate, (int) g_date_get_day(DateIn), (int) g_date_get_month(DateIn), (int)
                g_date_get_year(DateIn));
    }
    else {
      ret = g_date(&ITLDate, (int) g_date_get_day(DateIn), (int) g_date_get_month(DateIn), (int)
                   g_date_get_year(DateIn));
    }
  }

  cdate = g_date_new_dmy(ITLDate.day, ITLDate.month, ITLDate.year);

  return(cdate);
}

G_DEFINE_TYPE (ItlPrayer, itl_prayer, G_TYPE_OBJECT);
#define ITL_PRAYER_GET_PRIVATE(obj) \
(G_TYPE_INSTANCE_GET_PRIVATE ((obj), ITL_TYPE_PRAYER, ItlPrayerPrivate))

struct _ItlPrayerPrivate
{
  Method method;
  Location loc;
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
  // Set some default values:
  priv->loc.seaLevel    = 0;
  priv->loc.pressure    = 1010;
  priv->loc.temperature = 10;
}

/**
 * itl_prayer_new:
 *
 * Creates a new #ItlPrayer
 *
 * Return value: a new #ItlPrayer
 */
GObject*
itl_prayer_new (void)
{
  return g_object_new (ITL_TYPE_PRAYER, NULL);
}

/**
 * itl_prayer_setMethod:
 *
 * @prayer: (in): an #ItlPrayer
 * @n: (in): auto fill method: \
 *    0: none. Set to default or 0 \
 *    1: Egyptian General Authority of Survey \
 *    2: University of Islamic Sciences, Karachi (Shaf'i) \
 *    3: University of Islamic Sciences, Karachi (Hanafi) \
 *    4: Islamic Society of North America \
 *    5: Muslim World League (MWL) \
 *    6: Umm Al-Qurra, Saudi Arabia \
 *    7: Fixed Ishaa Interval (always 90) \
 *    8: Egyptian General Authority of Survey (Egypt)
 *
 * This function is used to auto fill the Method structure with predefined
 * data.
 */
void
itl_prayer_setMethod (ItlPrayer *prayer, gint n)
{
  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  getMethod((int) n, &prayer->priv->method);

  g_object_unref (prayer);
}

/**
 * itl_prayer_getPrayerTimes:
 *
 * @prayer: (in): an #ItlPrayer
 * @cdate: (in): Date for which to calculate prayer times
 *
 * This function calculates prayer times for the given date
 *
 * Return value: (transfer full) (element-type GLib.DateTime): 6 prayer times from Fajr till Isha'
 */
GList *
itl_prayer_getPrayerTimes (ItlPrayer *prayer, GDate *cdate)
{
  Date ITLDate;
  GDateTime *fajr, *shurooq, *dhuhr, *asr, *maghrib, *isha;
  GList *Prayers=NULL;
  Prayer ITLPrayer[6];

  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  ITLDate.day = g_date_get_day(cdate);
  ITLDate.month = g_date_get_month(cdate);
  ITLDate.year = g_date_get_year(cdate);

  getPrayerTimes (&prayer->priv->loc, &prayer->priv->method, &ITLDate,
                  ITLPrayer);

  fajr = g_date_time_new_local(ITLDate.year, ITLDate.month, ITLDate.day,
                               ITLPrayer[0].hour, ITLPrayer[0].minute,
                               ITLPrayer[0].second);
  shurooq = g_date_time_new_local(ITLDate.year, ITLDate.month, ITLDate.day,
                                  ITLPrayer[1].hour, ITLPrayer[1].minute,
                                  ITLPrayer[1].second);
  dhuhr = g_date_time_new_local(ITLDate.year, ITLDate.month, ITLDate.day,
                                ITLPrayer[2].hour, ITLPrayer[2].minute,
                                ITLPrayer[2].second);
  asr = g_date_time_new_local(ITLDate.year, ITLDate.month, ITLDate.day,
                              ITLPrayer[3].hour, ITLPrayer[3].minute,
                              ITLPrayer[3].second);
  maghrib = g_date_time_new_local(ITLDate.year, ITLDate.month, ITLDate.day,
                                  ITLPrayer[4].hour, ITLPrayer[4].minute,
                                  ITLPrayer[4].second);
  isha = g_date_time_new_local(ITLDate.year, ITLDate.month, ITLDate.day,
                               ITLPrayer[5].hour, ITLPrayer[5].minute,
                               ITLPrayer[5].second);

  Prayers = g_list_append(Prayers, fajr);
  Prayers = g_list_append(Prayers, shurooq);
  Prayers = g_list_append(Prayers, dhuhr);
  Prayers = g_list_append(Prayers, asr);
  Prayers = g_list_append(Prayers, maghrib);
  Prayers = g_list_append(Prayers, isha);

  g_object_unref (prayer);
  return(Prayers);
}

/**
 * itl_prayer_getNextDayFajr:
 *
 * @prayer: (in): an #ItlPrayer
 * @cdate: (in): Date for which to calculate Fajr for the day after
 *
 * This function calculates prayer times for the given date
 *
 * Return value: (transfer full): DateTime struct for next day fajr time
 */
GDateTime *
itl_prayer_getNextDayFajr (ItlPrayer *prayer, GDate *cdate)
{
  Date ITLDate;
  Prayer cPrayer;
  GDateTime *NextDayFajr;

  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  ITLDate.day = g_date_get_day(cdate);
  ITLDate.month = g_date_get_month(cdate);
  ITLDate.year = g_date_get_year(cdate);

  getNextDayFajr (&prayer->priv->loc, &prayer->priv->method, &ITLDate,
                  &cPrayer);

  NextDayFajr = g_date_time_new_local(ITLDate.year, ITLDate.month,
                                       ITLDate.day, cPrayer.hour,
                                       cPrayer.minute, cPrayer.second);

  g_object_unref (prayer);

  return(NextDayFajr);
}

/**
 * itl_prayer_getNorthQibla:
 *
 * @prayer: (in): an #ItlPrayer
 *
 * Get Qibla direction
 *
 * Return value: (transfer full): Qibla direction
 */
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

/**
 * itl_prayer_setLocation:
 *
 * @prayer: (in): an #ItlPrayer
 * @degreeLong: (in): Longitude in decimal degree.
 * @degreeLat: (in): Latitude in decimal degree.
 * @gmtDiff: (in): GMT difference at regular time.
 * @dst: (in): Daylight savings time switch; (0 if not used).
 *
 * Set location for which to calculate prayer times
 */
void
itl_prayer_setLocation (ItlPrayer *prayer, gdouble degreeLong, gdouble
                        degreeLat, gdouble gmtDiff, gboolean dst)
{
  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  prayer->priv->loc.degreeLong  = (double) degreeLong;
  prayer->priv->loc.degreeLat   = (double) degreeLat;
  prayer->priv->loc.gmtDiff     = (double) gmtDiff;
  prayer->priv->loc.dst         = (int) dst;

  g_object_unref (prayer);
}

/**
 * itl_prayer_set_seaLevel:
 *
 * @prayer: (in): an #ItlPrayer
 * @seaLevel: (in): Height above Sea level in meters
 *
 * Set sea level of location for which to calculate prayer times
 */
void
itl_prayer_set_seaLevel(ItlPrayer *prayer, gdouble seaLevel)
{
  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  prayer->priv->loc.seaLevel    = (double) seaLevel;

  g_object_unref (prayer);
}

/**
 * itl_prayer_set_pressure:
 *
 * @prayer: (in): an #ItlPrayer
 * @pressure: (in): Atmospheric pressure in millibars
 *
 * Set pressure of location for which to calculate prayer times
 */
void
itl_prayer_set_pressure(ItlPrayer *prayer, gdouble pressure)
{
  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  prayer->priv->loc.pressure    = (double) pressure;

  g_object_unref (prayer);
}

/**
 * itl_prayer_set_temperature:
 *
 * @prayer: (in): an #ItlPrayer
 * @temperature: (in): Temperature in Celsius degree
 *
 * Set temperature of location for which to calculate prayer times
 */
void
itl_prayer_set_temperature(ItlPrayer *prayer, gdouble temperature)
{
  g_return_if_fail (GOBJECT_IS_PRAYER (prayer));

  g_object_ref (prayer);

  prayer->priv->loc.temperature    = (double) temperature;

  g_object_unref (prayer);
}
