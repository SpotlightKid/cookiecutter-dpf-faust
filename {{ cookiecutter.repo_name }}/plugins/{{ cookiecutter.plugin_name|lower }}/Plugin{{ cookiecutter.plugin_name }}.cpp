/*
 * {{ cookiecutter.project_name }} audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier: {{ cookiecutter.project_license }}
 *
 * Copyright (C) {{ cookiecutter.year }} {{ cookiecutter.author_name }} <{{ cookiecutter.email }}>
{%- if cookiecutter.project_license == 'MIT' %}
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
{%- endif %}
 */

#include "Plugin{{ cookiecutter.plugin_name }}.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

Plugin{{ cookiecutter.plugin_name }}::Plugin{{ cookiecutter.plugin_name }}()
    : Plugin(paramCount, presetCount, 0)  // paramCount param(s), presetCount program(s), 0 states
{
    dsp = new {{ cookiecutter.plugin_name }};
    fSampleRate = getSampleRate();

    for (unsigned p = 0; p < paramCount; ++p) {
        Parameter param;
        initParameter(p, param);
        setParameterValue(p, param.ranges.def);
    }
}

Plugin{{ cookiecutter.plugin_name }}::~Plugin{{ cookiecutter.plugin_name }}() {
    delete dsp;
}

// -----------------------------------------------------------------------
// Init

void Plugin{{ cookiecutter.plugin_name }}::initParameter(uint32_t index, Parameter& parameter) {
    if (index >= paramCount)
        return;

    const {{ cookiecutter.plugin_name }}::ParameterRange* range = dsp->parameter_range(index);
    parameter.name = dsp->parameter_label(index);
    parameter.shortName = dsp->parameter_short_label(index);
    parameter.symbol = dsp->parameter_symbol(index);
    parameter.unit = dsp->parameter_unit(index);
    parameter.ranges.min = range->min;
    parameter.ranges.max = range->max;
    parameter.ranges.def = range->init;
    parameter.hints = kParameterIsAutomable;

    if (dsp->parameter_is_boolean(index))
        parameter.hints |= kParameterIsBoolean;
    if (dsp->parameter_is_integer(index))
        parameter.hints |= kParameterIsInteger;
    if (dsp->parameter_is_logarithmic(index))
        parameter.hints |= kParameterIsLogarithmic;
    if (dsp->parameter_is_trigger(index))
        parameter.hints |= kParameterIsTrigger;
}

/**
  Set the name of the program @a index.
  This function will be called once, shortly after the plugin is created.
*/
void Plugin{{ cookiecutter.plugin_name }}::initProgramName(uint32_t index, String& programName) {
    if (index < presetCount) {
        programName = factoryPresets[index].name;
    }
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void Plugin{{ cookiecutter.plugin_name }}::sampleRateChanged(double newSampleRate) {
    fSampleRate = newSampleRate;
    dsp->init(newSampleRate);
}

/**
  Get the current value of a parameter.
*/
float Plugin{{ cookiecutter.plugin_name }}::getParameterValue(uint32_t index) const {
    return dsp->get_parameter(index);
}

/**
  Change a parameter value.
*/
void Plugin{{ cookiecutter.plugin_name }}::setParameterValue(uint32_t index, float value) {
    if (index >= paramCount)
        return;

    const {{ cookiecutter.plugin_name }}::ParameterRange* range = dsp->parameter_range(index);
    dsp->set_parameter(index, CLAMP(value, range->min, range->max));
}

/**
  Load a program.
  The host may call this function from any context,
  including realtime processing.
*/
void Plugin{{ cookiecutter.plugin_name }}::loadProgram(uint32_t index) {
    if (index < presetCount) {
        for (int i=0; i < paramCount; i++) {
            setParameterValue(i, factoryPresets[index].params[i]);
        }
    }
}

// -----------------------------------------------------------------------
// Process

/**
  Plugin is activated.
*/
void Plugin{{ cookiecutter.plugin_name }}::activate() {
    fSampleRate = getSampleRate();
    dsp->init(fSampleRate);
}

{% set indent = " " * (cookiecutter.plugin_name | length + 17) %}
void Plugin{{ cookiecutter.plugin_name }}::run(const float** inputs, float** outputs,
{{ indent }}uint32_t frames) {
    dsp->process({% for i in range(cookiecutter.num_inputs | int) %}inputs[{{ i }}], {% endfor %}{% for i in range(cookiecutter.num_outputs | int) %}outputs[{{ i }}], {% endfor %}(unsigned)frames);
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new Plugin{{ cookiecutter.plugin_name }}();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
