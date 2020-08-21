declare name "{{ cookiecutter.plugin_name }}";
declare description "{{ cookiecutter.plugin_description }}";
declare author "{{ cookiecutter.author_name }}";
declare license "{{ cookiecutter.project_license }} license";

import("stdfaust.lib");

gain = hslider("[0]Gain [symbol: gain][abbrev: gain][unit: dB]", -6.0, -90.0, 30.0, 0.1):si.smoo;

process = _ * ba.db2linear(gain);
