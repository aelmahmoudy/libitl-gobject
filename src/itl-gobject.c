/* Copyright (C) 2011,2017 أحمد المحمودي (Ahmed El-Mahmoudy) <aelmahmoudy@users.sourceforge.net>

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
#include "itl-gobject-enums.h"
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

enum
{
  PROP_0,

  /* Location properties */
  PROP_DEGREE_LONG,
  PROP_DEGREE_LAT,
  PROP_GMT_DIFF,
  PROP_DST,
  PROP_SEA_LEVEL,
  PROP_PRESSURE,
  PROP_TEMPERATURE,
  /* Method properties */
  PROP_METHOD,
  PROP_FAJR_ANG,
  PROP_ISHAA_ANG,
  PROP_IMSAAK_ANG,
  PROP_FAJR_INV,
  PROP_ISHAA_INV,
  PROP_IMSAAK_INV,
  PROP_ROUND,
  PROP_MATHHAB,
  PROP_NEAREST_LAT,
  PROP_EXTREME,
  PROP_EXTREME_LAT,
  PROP_OFFSET,
  PROP_FAJR_OFFSET,
  PROP_SHUROOQ_OFFSET,
  PROP_DHUHR_OFFSET,
  PROP_ASR_OFFSET,
  PROP_MAGHRIB_OFFSET,
  PROP_ISHA_OFFSET
};

/* Defaults (copied from libitl's C library */
#define KAABA_LAT 21.423333
#define KAABA_LONG 39.823333
#define DEF_NEAREST_LATITUDE 48.5
#define DEF_IMSAAK_ANGLE 1.5

#define ITL_PRAYER_GET_PRIVATE(obj) \
(G_TYPE_INSTANCE_GET_PRIVATE ((obj), ITL_TYPE_PRAYER, ItlPrayerPrivate))

struct _ItlPrayerPrivate
{
  Method method;
  Location loc;
};

static void
itl_prayer_set_property (GObject      *object,
                         guint         prop_id,
                         const GValue *value,
                         GParamSpec   *pspec)
{
  ItlPrayer *prayer= ITL_PRAYER(object);

  switch (prop_id)
    {
    /* Location properties */
    case PROP_DEGREE_LONG:
      prayer->priv->loc.degreeLong = (double) g_value_get_double (value);
      break;
    case PROP_DEGREE_LAT:
      prayer->priv->loc.degreeLat = (double) g_value_get_double (value);
      break;
    case PROP_GMT_DIFF:
      prayer->priv->loc.gmtDiff = (double) g_value_get_double (value);
      break;
    case PROP_DST:
      prayer->priv->loc.dst = (int) g_value_get_boolean (value);
      break;
    case PROP_SEA_LEVEL:
      prayer->priv->loc.seaLevel = (double) g_value_get_double (value);
      break;
    case PROP_PRESSURE:
      prayer->priv->loc.pressure = (double) g_value_get_double (value);
      break;
    case PROP_TEMPERATURE:
      prayer->priv->loc.temperature = (double) g_value_get_double (value);
      break;
    /* Method properties */
    case PROP_METHOD:
      prayer->priv->method.method = (int) g_value_get_enum (value);
      break;
    case PROP_FAJR_ANG:
      prayer->priv->method.fajrAng = (double) g_value_get_double (value);
      break;
    case PROP_ISHAA_ANG:
      prayer->priv->method.ishaaAng = (double) g_value_get_double (value);
      break;
    case PROP_IMSAAK_ANG:
      prayer->priv->method.imsaakAng = (double) g_value_get_double (value);
      break;
    case PROP_FAJR_INV:
      prayer->priv->method.fajrInv = (int) g_value_get_int (value);
      break;
    case PROP_ISHAA_INV:
      prayer->priv->method.ishaaInv = (int) g_value_get_int (value);
      break;
    case PROP_IMSAAK_INV:
      prayer->priv->method.imsaakInv = (int) g_value_get_int (value);
      break;
    case PROP_ROUND:
      prayer->priv->method.round = (int) g_value_get_enum (value);
      break;
    case PROP_MATHHAB:
      prayer->priv->method.mathhab = (int) g_value_get_enum (value);
      break;
    case PROP_NEAREST_LAT:
      prayer->priv->method.nearestLat = (double) g_value_get_double (value);
      break;
    case PROP_EXTREME:
      prayer->priv->method.extreme = (int) g_value_get_enum (value);
      break;
    case PROP_EXTREME_LAT:
      prayer->priv->method.extremeLat = (double) g_value_get_double (value);
      break;
    case PROP_OFFSET:
      prayer->priv->method.offset = (int) g_value_get_boolean (value);
      break;
    case PROP_FAJR_OFFSET:
      prayer->priv->method.offList[0] = (double) g_value_get_double (value);
      break;
    case PROP_SHUROOQ_OFFSET:
      prayer->priv->method.offList[1] = (double) g_value_get_double (value);
      break;
    case PROP_DHUHR_OFFSET:
      prayer->priv->method.offList[2] = (double) g_value_get_double (value);
      break;
    case PROP_ASR_OFFSET:
      prayer->priv->method.offList[3] = (double) g_value_get_double (value);
      break;
    case PROP_MAGHRIB_OFFSET:
      prayer->priv->method.offList[4] = (double) g_value_get_double (value);
      break;
    case PROP_ISHA_OFFSET:
      prayer->priv->method.offList[5] = (double) g_value_get_double (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
itl_prayer_get_property (GObject      *object,
                         guint         prop_id,
                         GValue *value,
                         GParamSpec   *pspec)
{
  ItlPrayer *prayer= ITL_PRAYER(object);

  switch (prop_id)
    {
    /* Location properties */
    case PROP_DEGREE_LONG:
      g_value_set_double (value, (gdouble) prayer->priv->loc.degreeLong);
      break;
    case PROP_DEGREE_LAT:
      g_value_set_double (value, (gdouble) prayer->priv->loc.degreeLat);
      break;
    case PROP_GMT_DIFF:
      g_value_set_double (value, (gdouble) prayer->priv->loc.gmtDiff);
      break;
    case PROP_DST:
      g_value_set_boolean (value, (gboolean) prayer->priv->loc.dst);
      break;
    case PROP_SEA_LEVEL:
      g_value_set_double (value, (gdouble) prayer->priv->loc.seaLevel);
      break;
    case PROP_PRESSURE:
      g_value_set_double (value, (gdouble) prayer->priv->loc.pressure);
      break;
    case PROP_TEMPERATURE:
      g_value_set_double (value, (gdouble) prayer->priv->loc.temperature);
      break;
    /* Method properties */
    case PROP_METHOD:
      g_value_set_enum (value, (gint) prayer->priv->method.method);
      break;
    case PROP_FAJR_ANG:
      g_value_set_double (value, (gdouble) prayer->priv->method.fajrAng);
      break;
    case PROP_ISHAA_ANG:
      g_value_set_double (value, (gdouble) prayer->priv->method.ishaaAng);
      break;
    case PROP_IMSAAK_ANG:
      g_value_set_double (value, (gdouble) prayer->priv->method.imsaakAng);
      break;
    case PROP_FAJR_INV:
      g_value_set_int (value, (gint) prayer->priv->method.fajrInv);
      break;
    case PROP_ISHAA_INV:
      g_value_set_int (value, (gint) prayer->priv->method.ishaaInv);
      break;
    case PROP_IMSAAK_INV:
      g_value_set_int (value, (gint) prayer->priv->method.imsaakInv);
      break;
    case PROP_ROUND:
      g_value_set_enum (value, (gint) prayer->priv->method.round);
      break;
    case PROP_MATHHAB:
      g_value_set_enum (value, (gint) prayer->priv->method.mathhab);
      break;
    case PROP_NEAREST_LAT:
      g_value_set_double (value, (gdouble) prayer->priv->method.nearestLat);
      break;
    case PROP_EXTREME:
      g_value_set_enum (value, (gint) prayer->priv->method.extreme);
      break;
    case PROP_EXTREME_LAT:
      g_value_set_double (value, (gdouble) prayer->priv->method.extremeLat);
      break;
    case PROP_OFFSET:
      g_value_set_boolean (value, (gboolean) prayer->priv->method.offset);
      break;
    case PROP_FAJR_OFFSET:
      g_value_set_double (value, (gdouble) prayer->priv->method.offList[0]);
      break;
    case PROP_SHUROOQ_OFFSET:
      g_value_set_double (value, (gdouble) prayer->priv->method.offList[1]);
      break;
    case PROP_DHUHR_OFFSET:
      g_value_set_double (value, (gdouble) prayer->priv->method.offList[2]);
      break;
    case PROP_ASR_OFFSET:
      g_value_set_double (value, (gdouble) prayer->priv->method.offList[3]);
      break;
    case PROP_MAGHRIB_OFFSET:
      g_value_set_double (value, (gdouble) prayer->priv->method.offList[4]);
      break;
    case PROP_ISHA_OFFSET:
      g_value_set_double (value, (gdouble) prayer->priv->method.offList[5]);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
itl_prayer_finalize (GObject *object)
{
  G_OBJECT_CLASS (itl_prayer_parent_class)->finalize (object);
}

static void
itl_prayer_dispose (GObject *object)
{
  G_OBJECT_CLASS (itl_prayer_parent_class)->dispose (object);
}

static void
itl_prayer_class_init (ItlPrayerClass *klass)
{
  GObjectClass        *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize     = itl_prayer_finalize;
  gobject_class->dispose      = itl_prayer_dispose;
  gobject_class->set_property = itl_prayer_set_property;
  gobject_class->get_property = itl_prayer_get_property;

  /* Location properties */
  g_object_class_install_property (gobject_class,
                                   PROP_DEGREE_LONG,
                                   g_param_spec_double ("degree-long",
                                                        "Longitude", "Longitude in decimal degree",
                                                        -180.0, 180.0, KAABA_LONG,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class,
                                   PROP_DEGREE_LAT,
                                   g_param_spec_double ("degree-lat",
                                                        "Latitude", " Latitude in decimal degree",
                                                        -90.0, 90.0, KAABA_LAT,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class,
                                   PROP_GMT_DIFF,
                                   g_param_spec_double ("gmt-diff",
                                                        "GMT difference",
                                                        " GMT difference at regular time.",
                                                        -12.0, +14.0, 3.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class,
                                   PROP_DST,
                                   g_param_spec_boolean ("dst",
                                                         "Daylight savings time",
                                                         "Daylight savings time switch (0 if not used)",
                                                         FALSE,
                                                         G_PARAM_READABLE |
                                                         G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class,
                                   PROP_SEA_LEVEL,
                                   g_param_spec_double ("sea-level",
                                                        "Sea level",
                                                        "Height above Sea level in meters",
                                                        -G_MAXDOUBLE,
                                                        G_MAXDOUBLE, 0.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class,
                                   PROP_PRESSURE,
                                   g_param_spec_double ("pressure", "Pressure",
                                                        " Atmospheric pressure in millibars (the astronomical standard value is 1010)",
                                                        G_MINDOUBLE,
                                                        G_MAXDOUBLE, 1010.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class,
                                   PROP_TEMPERATURE,
                                   g_param_spec_double ("temperature",
                                                        "Temperature",
                                                        "Temperature in Celsius degree (the astronomical standard value is 10)",
                                                        -G_MAXDOUBLE,
                                                        G_MAXDOUBLE, 10.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));

  /* Method properties */
  g_object_class_install_property (gobject_class, PROP_METHOD,
                                   g_param_spec_enum ("method",
                                                        "Method",
                                                        "Calculation method",
                                                      ITL_TYPE_METHOD,
                                                      NONE,
                                                        G_PARAM_READABLE));
  g_object_class_install_property (gobject_class, PROP_FAJR_ANG,
                                   g_param_spec_double ("fajr-ang",
                                                        "Fajr angle",
                                                        "Fajr angle",
                                                        0.0,
                                                        20.0, 0.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_ISHAA_ANG,
                                   g_param_spec_double ("ishaa-ang",
                                                        "Ishaa' angle",
                                                        "Ishaa' angle",
                                                        0.0,
                                                        20.0, 0.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_FAJR_INV,
                                   g_param_spec_int ("fajr-inv",
                                                     "Fajr interval",
                                                     "Amount of minutes between Fajr and Shurooq (0 if not used)",
                                                     0, G_MAXINT, 0,
                                                     G_PARAM_READABLE |
                                                     G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_ISHAA_INV,
                                   g_param_spec_int ("ishaa-inv",
                                                     "Ishaa' interval",
                                                     "Amount of minutes between Ishaa and Maghrib (0 if not used)",
                                                     0, G_MAXINT, 0,
                                                     G_PARAM_READABLE |
                                                     G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_IMSAAK_INV,
                                   g_param_spec_int ("imsaak-inv",
                                                     "Imsaak Interval",
                                                     "Amount of minutes between Imsaak and Fajr",
                                                     0, G_MAXINT, 0,
                                                     G_PARAM_READABLE |
                                                     G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_IMSAAK_ANG,
                                   g_param_spec_double ("imsaak-ang",
                                                        "Imsaak angle",
                                                        " The angle difference between Imsaak and Fajr",
                                                        0, G_MAXINT, 0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_ROUND,
                                   g_param_spec_enum ("round", "Rounding",
                                                      "Method used for rounding seconds",
                                                      ITL_TYPE_ROUND_METHOD,
                                                      NOROUND, G_PARAM_READABLE
                                                      | G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_MATHHAB,
                                   g_param_spec_enum ("mathhab", "Math'hab",
                                                      "Asr prayer shadow ratio",
                                                      ITL_TYPE_MATHHAB, SHAFII,
                                                      G_PARAM_READABLE |
                                                      G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_NEAREST_LAT,
                                   g_param_spec_double ("nearest-lat",
                                                        "Nearest latitude",
                                                        "Latitude Used for the 'Nearest Latitude' extreme methods.",
                                                        -90.0, 90.0,
                                                        DEF_NEAREST_LATITUDE,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_EXTREME,
                                   g_param_spec_enum ("extreme", "Extreme",
                                                      "Extreme latitude calculation method",
                                                      ITL_TYPE_EXTREME_METHOD,
                                                      GOOD_INVALID,
                                                      G_PARAM_READABLE |
                                                      G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_EXTREME_LAT,
                                   g_param_spec_double ("extreme-lat",
                                                        "Extreme latitude",
                                                        "Latitude at which the extreme method should always be used",
                                                        -90.0, 90.0, 55.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_OFFSET,
                                   g_param_spec_boolean ("offset",
                                                     "Enable Offsets",
                                                     "This option allows you to add or subtract any amount of minutes to the daily computed prayer times based on values (in minutes) for each prayer in the offList array",
                                                     FALSE, G_PARAM_READABLE |
                                                     G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_FAJR_OFFSET,
                                   g_param_spec_double ("fajr-offset",
                                                        "Fajr offset",
                                                        "Fajr offset",
                                                        -G_MAXDOUBLE,
                                                        G_MAXDOUBLE, 0.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_SHUROOQ_OFFSET,
                                   g_param_spec_double ("shurooq-offset",
                                                        "Shurooq offset",
                                                        "Shurooq offset",
                                                        -G_MAXDOUBLE,
                                                        G_MAXDOUBLE, 0.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_DHUHR_OFFSET,
                                   g_param_spec_double ("dhuhr-offset",
                                                        "Dhuhr offset",
                                                        "Dhuhr offset",
                                                        -G_MAXDOUBLE,
                                                        G_MAXDOUBLE, 0.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_ASR_OFFSET,
                                   g_param_spec_double ("asr-offset",
                                                        "Asr offset",
                                                        "Asr offset",
                                                        -G_MAXDOUBLE,
                                                        G_MAXDOUBLE, 0.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_MAGHRIB_OFFSET,
                                   g_param_spec_double ("maghrib-offset",
                                                        "Maghrib offset",
                                                        "Maghrib offset",
                                                        -G_MAXDOUBLE,
                                                        G_MAXDOUBLE, 0.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));
  g_object_class_install_property (gobject_class, PROP_ISHA_OFFSET,
                                   g_param_spec_double ("isha-offset",
                                                        "Ishaa' offset",
                                                        "Ishaa' offset",
                                                        -G_MAXDOUBLE,
                                                        G_MAXDOUBLE, 0.0,
                                                        G_PARAM_READABLE |
                                                        G_PARAM_WRITABLE));

  g_type_class_add_private (gobject_class, sizeof (ItlPrayerPrivate));
}

static void
itl_prayer_init (ItlPrayer *self)
{
  ItlPrayerPrivate *priv;

  self->priv = priv = ITL_PRAYER_GET_PRIVATE (self);
  // Set some default values:
  priv->loc.seaLevel    = 0.0;
  priv->loc.pressure    = 1010.0;
  priv->loc.temperature = 10.0;
  getMethod(0, &priv->method);
}

/**
 * itl_prayer_new:
 *
 * Creates a new #ItlPrayer
 *
 * Return value: a new #ItlPrayer
 */
ItlPrayer*
itl_prayer_new (void)
{
  return g_object_new (ITL_TYPE_PRAYER, NULL);
}

/**
 * itl_prayer_setMethod:
 *
 * @prayer: (in): an #ItlPrayer
 * @n: (in): auto fill method
 *
 * This function is used to auto fill the Method structure with predefined
 * data.
 */
void
itl_prayer_setMethod (ItlPrayer *prayer, ItlMethod n)
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

  g_return_val_if_fail (GOBJECT_IS_PRAYER (prayer), 0);

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

  g_return_val_if_fail (GOBJECT_IS_PRAYER (prayer), 0);

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

  g_return_val_if_fail (GOBJECT_IS_PRAYER (prayer), 0);

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
