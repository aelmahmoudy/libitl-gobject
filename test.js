const GLib = imports.gi.GLib;
const Itl = imports.gi.Itl;
const Notify = imports.gi.Notify;

function PrayerName(PrayerIdx)
{
  switch(PrayerIdx) {
    case 0: return "Fajr";
    case 1: return "Shurooq";
    case 2: return "Dhuhr";
    case 3: return "'Asr";
    case 4: return "Maghrib";
    case 5: return "'Ishaa";
  }
  return undefined;
}

let now = new Date();
let HijriNow=Itl.h_date(now.getDate(), now.getMonth()+1, now.getFullYear());
let text = HijriNow.get_day() + " " + HijriNow.get_month() + " " + HijriNow.get_year();

// Get prayer times:
let PrayerObj = new Itl.Prayer();
PrayerObj.setMethod(Itl.Method.EGYPT_NEW); // Egyptian survey method
PrayerObj.setLocation(31.4, 30.13, 2.0, 0); // Location for Cairo
let today = new GLib.Date.new_dmy(now.getDate(), now.getMonth()+1, now.getFullYear());
let PrayerList = PrayerObj.getPrayerTimes(today);

text+=" " + today.get_day() + "/" + today.get_month() + "/" + today.get_year();
for(let i=0; i<6; i++) {
  text += ("\n" + PrayerName(i) + ": " + PrayerList[i].get_hour() + ":" + PrayerList[i].get_minute());
}
text += "\n";
text += "\ndegreeLong=" + PrayerObj.degreeLong;

Notify.init('Salat');
n = Notify.Notification.new('Prayer times', text, null);
n.show();
