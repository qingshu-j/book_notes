(function(exports, require, module, __filename, __dirname) {
    /*! For license information please see index.js.LICENSE.txt */
    (()=>{
        var a = {
            19: (a,e,t)=>{
                const n = t(770)
                  , r = [{
                    name: "RGBColor",
                    code: 3
                }, {
                    name: "HSBColorEnum",
                    code: 4
                }, {
                    name: "labColor",
                    code: 6
                }]
                  , i = {
                    red: {
                        red: 100,
                        green: 0,
                        blue: 0,
                        constant: 0
                    },
                    green: {
                        red: 0,
                        green: 100,
                        blue: 0,
                        constant: 0
                    },
                    blue: {
                        red: 0,
                        green: 0,
                        blue: 100,
                        constant: 0
                    },
                    gray: {
                        red: 40,
                        green: 40,
                        blue: 20,
                        constant: 0
                    }
                };
                class s {
                    constructor() {}
                    static Instance() {
                        return this._instance || (this._instance = new s),
                        this._instance
                    }
                    async getGradientMap() {
                        return await this._getGradientMap()
                    }
                    async getCurves() {
                        return await this._getCurves()
                    }
                    async toggleHueSaturationColorize() {
                        const a = await this._getHueSaturation();
                        a && (a.colorize = !a.colorize,
                        await this._modifyAdjustment(a))
                    }
                    async toggleColorBalancePreserveLuminosity() {
                        const a = await this._getAdjustment();
                        if (!a)
                            return;
                        const e = this._getColorBalance(a.rawData);
                        await this._modifyAdjustment({
                            _obj: "colorBalance",
                            shadowLevels: [e.shadows.cyanRed, e.shadows.magentaGreen, e.shadows.yellowBlue],
                            midtoneLevels: [e.midtones.cyanRed, e.midtones.magentaGreen, e.midtones.yellowBlue],
                            highlightLevels: [e.highlights.cyanRed, e.highlights.magentaGreen, e.highlights.yellowBlue],
                            preserveLuminosity: !e.preserveLuminosity
                        })
                    }
                    async autoBrightnessAndContrast(a) {
                        await this._modifyAdjustment({
                            _obj: "brightnessEvent",
                            brightness: 0,
                            center: 0,
                            useLegacy: a
                        }),
                        await n.executeBatchPlay({
                            _obj: "set",
                            _target: [{
                                _ref: "adjustmentLayer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }],
                            to: {
                                _obj: "brightnessEvent",
                                auto: !0,
                                useLegacy: a
                            }
                        })
                    }
                    async addCurve(a) {
                        const e = await this._getCurves();
                        if (!e)
                            return;
                        const t = e.adjustment[a]
                          , n = t.curve[t.curve.length - 2];
                        t.curve.splice(t.curve.length - 1, 0, {
                            _obj: "paint",
                            horizontal: n.horizontal + 4,
                            vertical: n.vertical
                        }),
                        await this._modifyAdjustment(e)
                    }
                    async resetCurveAdjustment(a) {
                        const e = await this._getCurves();
                        e && (e.adjustment[a].curve = [{
                            _obj: "paint",
                            horizontal: 0,
                            vertical: 0
                        }, {
                            _obj: "paint",
                            horizontal: 255,
                            vertical: 255
                        }],
                        await this._modifyAdjustment(e))
                    }
                    async deleteCurve(a, e) {
                        const t = await this._getCurves();
                        t && (t.adjustment[a].curve.splice(e, 1),
                        await this._modifyAdjustment(t))
                    }
                    async adjustCurves(a, e, t, r) {
                        const i = await this._getCurves();
                        if (!i)
                            return;
                        const s = i.adjustment[a]
                          , o = e === s.curve.length - 1 ? 255 : s.curve[e + 1].horizontal - 4
                          , l = 0 === e ? 0 : s.curve[e - 1].horizontal + 4
                          , c = s.curve[e];
                        c.horizontal = n.maxMin(c.horizontal + t, o, l),
                        c.vertical = n.maxMin(c.vertical + r, 255, 0),
                        await this._modifyAdjustment(i)
                    }
                    async nextGradientMapNoiseColorSpace() {
                        const a = await this._getGradientMap();
                        if (!a)
                            return;
                        let e = r.findIndex((e=>e.name === a.gradient.colorSpace._value));
                        ++e >= r.length && (e = 0),
                        a.gradient.colorSpace._value = r[e].name,
                        await this._modifyAdjustment(a)
                    }
                    async adjustGradientMapNoiseMinimum(a, e, t) {
                        await this._adjustGradientMapNoiseMinMax("minimum", a, e, t)
                    }
                    async adjustGradientMapNoiseMaximum(a, e, t) {
                        await this._adjustGradientMapNoiseMinMax("maximum", a, e, t)
                    }
                    async adjustGradientMapNoiseRoughness(a) {
                        const e = await this._getGradientMap();
                        e && (e.gradient.smoothness = 0 === a ? 2048 : this._adjustByPercentage(e.gradient.smoothness, a, 4096),
                        await this._modifyAdjustment(e))
                    }
                    async toggleGradientMapDither() {
                        const a = await this._getGradientMap();
                        a && (a.dither = !a.dither,
                        await this._modifyAdjustment(a))
                    }
                    async toggleGradientMapReverse() {
                        const a = await this._getGradientMap();
                        a && (a.reverse = !a.reverse,
                        await this._modifyAdjustment(a))
                    }
                    async toggleGradientMapType() {
                        const a = await this._getGradientMap();
                        a && (a.gradient.gradientForm._value = "colorNoise" === a.gradient.gradientForm._value ? "customStops" : "colorNoise",
                        await this._modifyAdjustment(a))
                    }
                    async gradientMapSolidColorAdd() {
                        const a = await this._getGradientMap();
                        if (!a)
                            return;
                        const e = await colorInstance.getForegroundRGBColor()
                          , t = this._newGradientMapColor(0, 50, e[0], e[1], e[2]);
                        a.gradient.colors.push(t),
                        await this._modifyAdjustment(a)
                    }
                    async gradientMapTransparencyAdd() {
                        const a = await this._getGradientMap();
                        if (!a)
                            return;
                        const e = this._newGradientTransparency(0, 50, 100);
                        a.gradient.transparency.push(e),
                        await this._modifyAdjustment(a)
                    }
                    async gradientMapSolidColorDelete(a) {
                        const e = await this._getGradientMap();
                        e && (e.gradient.colors.splice(a, 1),
                        await this._modifyAdjustment(e))
                    }
                    async gradientMapTransparencyDelete(a) {
                        const e = await this._getGradientMap();
                        e && (e.gradient.transparency.splice(a, 1),
                        await this._modifyAdjustment(e))
                    }
                    async toggleGradientMapNoiseRestrictColors() {
                        const a = await this._getGradientMap();
                        a && (a.gradient.vectorColor = !a.gradient.vectorColor,
                        await this._modifyAdjustment(a))
                    }
                    async toggleGradientMapNoiseShowTransparency() {
                        const a = await this._getGradientMap();
                        a && (a.gradient.showTransparency = !a.gradient.showTransparency,
                        await this._modifyAdjustment(a))
                    }
                    async gradientMapNoiseRandomize() {
                        const a = await this._getGradientMap();
                        a && (a.gradient.randomSeed = Math.floor(2147483647 * Math.random()) + 1,
                        await this._modifyAdjustment(a))
                    }
                    async adjustGradientMapSolidColorSmoothness(a) {
                        const e = await this._getGradientMap();
                        e && (e.gradient.interfaceIconFrameDimmed = 0 === a ? 4096 : this._adjustByPercentage(e.gradient.interfaceIconFrameDimmed, a, 4096),
                        await this._modifyAdjustment(e))
                    }
                    async adjustGradientMapSolidColor(a, e, t, n) {
                        const r = await this._getGradientMap();
                        if (!r)
                            return;
                        const i = r.gradient.colors[a]
                          , s = colorInstance.adjustHSBColor(e, t, n, colorInstance.toHSB(i.color));
                        i.color = colorInstance.RGBToDescriptor(a.hsv.rgb(s)),
                        await this._modifyAdjustment(r)
                    }
                    async adjustGradientMapSolidColorLocation(a, e) {
                        const t = await this._getGradientMap();
                        if (!t)
                            return;
                        const n = t.gradient.colors[a];
                        n.location = this._adjustByPercentage(n.location, e, 4096),
                        await this._modifyAdjustment(t)
                    }
                    async adjustGradientMapSolidColorMidpoint(a, e) {
                        const t = await this._getGradientMap();
                        if (!t)
                            return;
                        const r = t.gradient.colors[a];
                        r.midpoint = n.maxMin(r.midpoint + e, 100, 0),
                        await this._modifyAdjustment(t)
                    }
                    async adjustGradientMapTransparencyOpacity(a, e) {
                        const t = await this._getGradientMap();
                        if (!t)
                            return;
                        const r = t.gradient.transparency[a];
                        r.opacity._value = 0 === e ? 100 : n.maxMin(r.opacity._value + e, 100, 0),
                        await this._modifyAdjustment(t)
                    }
                    async adjustGradientMapTransparencyLocation(a, e) {
                        const t = await this._getGradientMap();
                        if (!t)
                            return;
                        const n = t.gradient.transparency[a];
                        n.location = this._adjustByPercentage(n.location, e, 4096),
                        await this._modifyAdjustment(t)
                    }
                    async adjustGradientMapTransparencyMidpoint(a, e) {
                        const t = await this._getGradientMap();
                        if (!t)
                            return;
                        const r = t.gradient.transparency[a];
                        r.midpoint = n.maxMin(r.midpoint + e, 100, 0),
                        await this._modifyAdjustment(t)
                    }
                    async toggleSelectiveColorMethod() {
                        const a = await this._getSelectiveColor();
                        a.method._value = "relative" === a.method._value ? "absolute" : "relative",
                        await this._modifyAdjustment(a)
                    }
                    async adjustSelectiveColor(a, e, t) {
                        const r = await this._getSelectiveColor()
                          , i = r.colorCorrection[a][e];
                        i._value = 0 === t ? 0 : n.maxMin(i._value + t, 100, -100),
                        await this._modifyAdjustment(r)
                    }
                    async adjustThresholdLevel(a) {
                        const e = await this._getThreshold();
                        e && (e.level = 0 === a ? 128 : n.maxMin(e.level + a, 255, 1),
                        await this._modifyAdjustment(e))
                    }
                    async adjustPosterizeLevels(a) {
                        const e = await this._getPosterize();
                        e && (e.levels = 0 === a ? 4 : n.maxMin(e.levels + a, 255, 2),
                        await this._modifyAdjustment(e))
                    }
                    async toggleMonochromaticChannelMixer() {
                        let a, e = await this._getChannelMixer();
                        e && (a = e.monochromatic ? {
                            _obj: "channelMixer",
                            red: e.gray,
                            green: e.gray,
                            blue: e.gray,
                            monochromatic: !1
                        } : {
                            _obj: "channelMixer",
                            gray: {
                                _obj: "channelMatrix",
                                red: {
                                    _unit: "percentUnit",
                                    _value: 40
                                },
                                green: {
                                    _unit: "percentUnit",
                                    _value: 40
                                },
                                blue: {
                                    _unit: "percentUnit",
                                    _value: 20
                                },
                                constant: {
                                    _unit: "percentUnit",
                                    _value: 0
                                }
                            },
                            monochromatic: !0
                        },
                        await this._modifyAdjustment(a))
                    }
                    async resetChannelMixer() {
                        const a = await this._getChannelMixer();
                        a && (Object.keys(i).forEach((e=>{
                            a[e] && Object.keys(i[e]).forEach((t=>{
                                a[e][t] = i[e][t]
                            }
                            ))
                        }
                        )),
                        await this._modifyAdjustment(a))
                    }
                    async adjustChannelMixer(a, e, t) {
                        const r = await this._getChannelMixer();
                        r && (r.monochromatic && (a = "gray"),
                        r[a][e] = 0 === t ? i[a][e] : n.maxMin(r[a][e]._value + t, 200, -200),
                        await this._modifyAdjustment(r))
                    }
                    async adjustPhotoFilterDensity(a) {
                        const e = await this._getPhotoFilter();
                        e.density = 0 === a ? 25 : n.maxMin(e.density + a, 100, 1),
                        await this._modifyAdjustment(e)
                    }
                    async adjustPhotoFilterColor(a, e, t) {
                        const n = await this._getPhotoFilter()
                          , r = n.color;
                        let i = colorIndex.lab.hsv([r.luminance, r.a, r.b]);
                        i = colorInstance.adjustHSBColor(a, e, t, i),
                        n.color = colorInstance.HSBToDescriptor(i),
                        await this._modifyAdjustment(n)
                    }
                    async togglePhotoFilterPreserveLuminosity() {
                        const a = await this._getPhotoFilter();
                        a.preserveLuminosity = !a.preserveLuminosity,
                        await this._modifyAdjustment(a)
                    }
                    async adjustExposure(a, e, t) {
                        const n = await this._getAdjustment();
                        n && await this._modifyExposure(a, e, n.rawData, t)
                    }
                    async adjustBrightness(a, e, t) {
                        const n = await this._getAdjustment();
                        n && await this._modifyBrightness(a, e, n.rawData, 0)
                    }
                    async adjustLevels(a, e, t) {
                        const n = await this._getAdjustment();
                        n && await this._modifyLevels(a, e, n.rawData, t)
                    }
                    async adjustVibrance(a, e, t) {
                        const n = await this._getAdjustment();
                        n && await this._modifyVibrance(a, e, n.rawData, t)
                    }
                    async adjustHueSaturationHue(a, e) {
                        const t = await this._getHueSaturation();
                        if (!t)
                            return;
                        const r = t.adjustment[e];
                        t.colorize ? r.hue = 0 === a ? 180 : n.maxMin(r.hue + a, 359, 0) : r.hue = 0 === a ? 0 : n.maxMin(r.hue + a, 180, -180),
                        await this._modifyAdjustment(t)
                    }
                    async adjustHueSaturationSaturation(a, e) {
                        const t = await this._getHueSaturation();
                        if (!t)
                            return;
                        const r = t.adjustment[e];
                        t.colorize ? r.saturation = 0 === a ? 25 : n.maxMin(r.saturation + a, 100, 0) : r.saturation = 0 === a ? 0 : n.maxMin(r.saturation + a, 100, -100),
                        await this._modifyAdjustment(t)
                    }
                    async adjustHueSaturationLightness(a, e) {
                        const t = await this._getHueSaturation();
                        if (!t)
                            return;
                        const r = t.adjustment[e];
                        r.lightness = 0 === a ? 0 : n.maxMin(r.lightness + a, 100, -100),
                        await this._modifyAdjustment(t)
                    }
                    async adjustHueSaturationBeginRamp(a, e) {
                        const t = await this._getHueSaturation();
                        if (!t || t.colorize)
                            return;
                        const r = t.adjustment[e];
                        let i = 315 + 60 * (e - 1);
                        i = i > 360 ? i - 360 : i,
                        r.beginRamp = 0 === a ? i : n.maxMin(r.beginRamp + a, 360, 0),
                        await this._modifyAdjustment(t)
                    }
                    async adjustHueSaturationBeginSustain(a, e) {
                        const t = await this._getHueSaturation();
                        if (!t || t.colorize)
                            return;
                        const r = t.adjustment[e];
                        let i = 345 + 60 * (e - 1);
                        i = i > 360 ? i - 360 : i,
                        r.beginSustain = 0 === a ? i : n.maxMin(r.beginSustain + a, 360, 0),
                        await this._modifyAdjustment(t)
                    }
                    async adjustHueSaturationEndSustain(a, e) {
                        const t = await this._getHueSaturation();
                        if (!t || t.colorize)
                            return;
                        const r = t.adjustment[e];
                        let i = 15 + 60 * (e - 1);
                        i = i > 360 ? i - 360 : i,
                        r.endSustain = 0 === a ? i : n.maxMin(r.endSustain + a, 360, 0),
                        await this._modifyAdjustment(t)
                    }
                    async adjustHueSaturationEndRamp(a, e) {
                        const t = await this._getHueSaturation();
                        if (!t || t.colorize)
                            return;
                        const r = t.adjustment[e];
                        let i = 45 + 60 * (e - 1);
                        i = i > 360 ? i - 360 : i,
                        r.endRamp = 0 === a ? i : n.maxMin(r.endRamp + a, 360, 0),
                        await this._modifyAdjustment(t)
                    }
                    async adjustColorBalance(a, e, t, n) {
                        const r = await this._getAdjustment();
                        r && await this._modifyColorBalance(a, e, t, r.rawData, n)
                    }
                    async adjustBlackAndWhite(a, e, t) {
                        const n = await this._getAdjustment();
                        n && await this._modifyBlackAndWhite(a, e, n.rawData, t)
                    }
                    async adjust(a, e) {
                        const t = await this._getAdjustment();
                        if (!t)
                            return;
                        const n = this._getKey(e, t._obj);
                        if (n)
                            switch (t._obj) {
                            case "exposure":
                                await this._modifyExposure(a, n, t.rawData, 0);
                                break;
                            case "brightnessEvent":
                                await this._modifyBrightness(a, n, t.rawData, 0);
                                break;
                            case "levels":
                                await this._modifyLevels(a, n, t.rawData, 0);
                                break;
                            case "vibrance":
                                await this._modifyVibrance(a, n, t.rawData, 0);
                                break;
                            case "hueSaturation":
                                await this._modifyHueSaturation(a, n, t.rawData, 0);
                                break;
                            case "colorBalance":
                                const e = n;
                                await this._modifyColorBalance(a, e.colorType, e.key, t.rawData, 0);
                                break;
                            case "blackAndWhite":
                                await this._modifyBlackAndWhite(a, n, t.rawData, 0);
                                break;
                            default:
                                return
                            }
                    }
                    async create(a) {
                        let e = {};
                        switch (a) {
                        case "threshold":
                            e = {
                                _obj: "thresholdClassEvent"
                            };
                            break;
                        case "brightness":
                            e = {
                                _obj: "brightnessEvent",
                                useLegacy: !0
                            };
                            break;
                        case "blackWhite":
                            e = {
                                _obj: "blackAndWhite"
                            };
                            break;
                        case "gradientMap":
                            e = {
                                _obj: "gradientMapClass"
                            };
                            break;
                        default:
                            e = {
                                _obj: a
                            }
                        }
                        await n.executeBatchPlay({
                            _obj: "make",
                            _target: {
                                _ref: "adjustmentLayer"
                            },
                            using: {
                                _obj: "adjustmentLayer",
                                type: e
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async _modifyExposure(a, e, t, n) {
                        let r = 2;
                        const i = {
                            exposure: t.readFloatBE(r),
                            offset: t.readFloatBE(r += 4),
                            gamma: t.readFloatBE(r += 4)
                        };
                        if (0 === a)
                            i[e] = n;
                        else
                            switch (e) {
                            case "exposure":
                                i.exposure += .02 * a;
                                break;
                            case "offset":
                                i.offset += .001 * a;
                                break;
                            case "gamma":
                                i.gamma += -.01 * a
                            }
                        await this._modifyAdjustment({
                            _obj: "exposure",
                            presetKind: {
                                _enum: "presetKindType",
                                _value: "presetKindCustom"
                            },
                            exposure: i.exposure,
                            offset: i.offset,
                            gammaCorrection: i.gamma
                        })
                    }
                    async _modifyBrightness(a, e, t, n) {
                        let r = 0;
                        const i = {
                            brightness: t.readInt16BE(r),
                            contrast: t.readInt16BE(r += 2)
                        };
                        i[e] = 0 === a ? n : i[e] + a,
                        await this._modifyAdjustment({
                            _obj: "brightnessEvent",
                            brightness: i.brightness,
                            center: i.contrast,
                            useLegacy: !0
                        })
                    }
                    async _modifyLevels(a, e, t, n) {
                        let r = 2;
                        const i = {
                            inBlack: t.readInt16BE(r),
                            inWhite: t.readInt16BE(r += 2),
                            outBlack: t.readInt16BE(r += 2),
                            outWhite: t.readInt16BE(r += 2),
                            gamma: t.readInt16BE(r += 2) / 100
                        };
                        0 === a ? i[e] = n : "gamma" === e ? i.gamma += -.01 * a : i[e] += a,
                        await this._modifyAdjustment({
                            _obj: "levels",
                            presetKind: {
                                _enum: "presetKindType",
                                _value: "presetKindCustom"
                            },
                            adjustment: [{
                                _obj: "levelsAdjustment",
                                channel: {
                                    _ref: "channel",
                                    _enum: "channel",
                                    _value: "composite"
                                },
                                input: [i.inBlack, i.inWhite],
                                gamma: i.gamma,
                                output: [i.outBlack, i.outWhite]
                            }]
                        })
                    }
                    async _modifyVibrance(a, e, t, n) {
                        let r = 40;
                        const i = {
                            vibrance: 0,
                            saturation: 0
                        };
                        i.vibrance = t.byteLength >= r ? t.readInt16BE(r) : 0,
                        r = 0 === i.vibrance ? r - 4 : r + 16,
                        i.saturation = t.byteLength >= r ? t.readInt16BE(r) : 0,
                        i[e] = 0 === a ? n : i[e] + a,
                        await this._modifyAdjustment({
                            _obj: "vibrance",
                            presetKind: {
                                _enum: "presetKindType",
                                _value: "presetKindCustom"
                            },
                            vibrance: i.vibrance,
                            saturation: i.saturation
                        })
                    }
                    async _modifyHueSaturation(a, e, t, n) {
                        let r = 10;
                        const i = {
                            hue: t.readInt16BE(r),
                            saturation: t.readInt16BE(r += 2),
                            lightness: t.readInt16BE(r += 2)
                        };
                        i[e] = 0 === a ? n : i[e] + a,
                        await this._modifyAdjustment({
                            _obj: "hueSaturation",
                            adjustment: [{
                                _obj: "hueSatAdjustmentV2",
                                hue: i.hue,
                                saturation: i.saturation,
                                lightness: i.lightness
                            }]
                        })
                    }
                    async _modifyColorBalance(a, e, t, n, r) {
                        const i = this._getColorBalance(n);
                        i[e][t] = 0 === a ? r : a + i[e][t],
                        await this._modifyAdjustment({
                            _obj: "colorBalance",
                            shadowLevels: [i.shadows.cyanRed, i.shadows.magentaGreen, i.shadows.yellowBlue],
                            midtoneLevels: [i.midtones.cyanRed, i.midtones.magentaGreen, i.midtones.yellowBlue],
                            highlightLevels: [i.highlights.cyanRed, i.highlights.magentaGreen, i.highlights.yellowBlue],
                            preserveLuminosity: i.preserveLuminosity
                        })
                    }
                    async _modifyBlackAndWhite(a, e, t, n) {
                        let r = 36;
                        const i = {
                            red: t.readInt16BE(r),
                            yellow: t.readInt16BE(r += 16),
                            green: t.readInt16BE(r += 16),
                            cyan: t.readInt16BE(r += 16),
                            blue: t.readInt16BE(r += 16),
                            magenta: t.readInt16BE(r += 16)
                        };
                        i[e] = 0 === a ? n : a + i[e],
                        await this._modifyAdjustment({
                            _obj: "blackAndWhite",
                            red: i.red,
                            yellow: i.yellow,
                            green: i.green,
                            cyan: i.cyan,
                            blue: i.blue,
                            magenta: i.magenta
                        })
                    }
                    async _getAdjustment() {
                        const a = (await n.executeBatchPlay({
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "adjustment"
                                }, {
                                    _ref: "adjustmentLayer",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }))[0].adjustment;
                        return a ? {
                            _obj: a[0]._obj,
                            rawData: new Buffer(a[0].legacyContentData)
                        } : void 0
                    }
                    async _modifyAdjustment(a) {
                        await n.executeBatchPlay({
                            _obj: "set",
                            _target: {
                                _ref: "adjustmentLayer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            to: a,
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    _getKey(a, e) {
                        switch (a) {
                        case "adjustExposure":
                            switch (e) {
                            case "exposure":
                                return "exposure";
                            case "brightnessEvent":
                                return "brightness";
                            case "hueSaturation":
                                return "lightness";
                            case "colorBalance":
                                return {
                                    colorType: "shadows",
                                    key: "yellowBlue"
                                };
                            default:
                                return
                            }
                        case "adjustContrast":
                            switch (e) {
                            case "exposure":
                            case "levels":
                                return "gamma";
                            case "brightnessEvent":
                                return "contrast";
                            case "colorBalance":
                                return {
                                    colorType: "shadows",
                                    key: "cayanRed"
                                };
                            default:
                                return
                            }
                        case "adjustClarity":
                            return "colorBalance" === e ? {
                                colorType: "shadows",
                                key: "magentaGreen"
                            } : void 0;
                        case "adjustBlacks":
                            switch (e) {
                            case "exposure":
                                return "offset";
                            case "levels":
                                return "inBlack";
                            default:
                                return
                            }
                        case "adjustShadows":
                            return "colorBalance" === e ? {
                                colorType: "shadows",
                                key: "cayanRed"
                            } : void 0;
                        case "adjustBlacksFn":
                            return "levels" === e ? "outBlack" : void 0;
                        case "adjustWhites":
                            switch (e) {
                            case "colorBalance":
                                return {
                                    colorType: "midtones",
                                    key: "yellowBlue"
                                };
                            case "levels":
                                return "inWhite";
                            default:
                                return
                            }
                        case "adjustHighlights":
                            return "colorBalance" === e ? {
                                colorType: "midtones",
                                key: "magentaGreen"
                            } : void 0;
                        case "adjustWhitesFn":
                            return "levels" === e ? "outWhite" : void 0;
                        case "adjustSaturation":
                            switch (e) {
                            case "vibrance":
                            case "hueSaturation":
                                return "saturation";
                            case "colorBalance":
                                return {
                                    colorType: "highlights",
                                    key: "yellowBlue"
                                };
                            default:
                                return
                            }
                        case "adjustVibrance":
                            switch (e) {
                            case "vibrance":
                                return "vibrance";
                            case "colorBalance":
                                return {
                                    colorType: "shadows",
                                    key: "cyanRed"
                                };
                            default:
                                return
                            }
                        case "adjustTemperature":
                            switch (e) {
                            case "hueSaturation":
                                return "hue";
                            case "colorBalance":
                                return {
                                    colorType: "highlights",
                                    key: "cyanRed"
                                };
                            default:
                                return
                            }
                        case "adjustTint":
                            switch (e) {
                            case "hueSaturation":
                                return "hue";
                            case "colorBalance":
                                return {
                                    colorType: "highlights",
                                    key: "magentaGreen"
                                };
                            default:
                                return
                            }
                        case "adjustScroll1":
                            switch (e) {
                            case "brightnessEvent":
                                return "brightness";
                            case "levels":
                                return "inBlack";
                            case "exposure":
                            case "vibrance":
                                return "exposure";
                            case "hueSaturation":
                                return "hue";
                            case "colorBalance":
                                return {
                                    colorType: "shadows",
                                    key: "cyanRed"
                                };
                            case "blackAndWhite":
                                return "red";
                            default:
                                return
                            }
                        case "adjustScroll2":
                            switch (e) {
                            case "brightnessEvent":
                                return "contrast";
                            case "levels":
                                return "gamma";
                            case "exposure":
                                return "offset";
                            case "vibrance":
                            case "hueSaturation":
                                return "saturation";
                            case "colorBalance":
                                return {
                                    colorType: "shadows",
                                    key: "magentaGreen"
                                };
                            case "blackAndWhite":
                                return "magentaGreen";
                            default:
                                return
                            }
                        case "adjustScroll3":
                            switch (e) {
                            case "levels":
                                return "inWhite";
                            case "exposure":
                                return "gamma";
                            case "hueSaturation":
                                return "lightness";
                            case "colorBalance":
                                return {
                                    colorType: "shadows",
                                    key: "yellowBlue"
                                };
                            case "blackAndWhite":
                                return "yellow";
                            default:
                                return
                            }
                        case "adjustScroll4":
                            switch (e) {
                            case "levels":
                                return "outBlack";
                            case "colorBalance":
                                return {
                                    colorType: "midtones",
                                    key: "cyanRed"
                                };
                            case "blackAndWhite":
                                return "green";
                            default:
                                return
                            }
                        case "adjustScroll5":
                            switch (e) {
                            case "levels":
                                return "outWhite";
                            case "colorBalance":
                                return {
                                    colorType: "midtones",
                                    key: "magentaGreen"
                                };
                            case "blackAndWhite":
                                return "cyan";
                            default:
                                return
                            }
                        case "adjustScroll6":
                            switch (e) {
                            case "colorBalance":
                                return {
                                    colorType: "midtones",
                                    key: "yellowBlue"
                                };
                            case "blackAndWhite":
                                return "blue";
                            default:
                                return
                            }
                        case "adjustScroll7":
                            return "colorBalance" === e ? {
                                colorType: "highlights",
                                key: "cyanRed"
                            } : void 0;
                        case "adjustScroll8":
                            switch (e) {
                            case "colorBalance":
                                return {
                                    colorType: "highlights",
                                    key: "magentaGreen"
                                };
                            case "blackAndWhite":
                                return "magenta";
                            default:
                                return
                            }
                        case "adjustScrollFn1":
                            return "colorBalance" === e ? {
                                colorType: "highlights",
                                key: "yellowBlue"
                            } : void 0;
                        default:
                            return
                        }
                    }
                    async _getPhotoFilter() {
                        const a = await this._getAdjustment();
                        if (!a)
                            return;
                        let e = 4;
                        return {
                            _obj: "photoFilter",
                            color: {
                                _obj: "labColor",
                                luminance: a.rawData.readInt16BE(e) / 100,
                                a: a.rawData.readInt16BE(e += 2) / 100,
                                b: a.rawData.readInt16BE(e += 2) / 100
                            },
                            density: a.rawData[15],
                            preserveLuminosity: Boolean(a.rawData[16])
                        }
                    }
                    async _getChannelMixer() {
                        const a = await this._getAdjustment();
                        if (!a)
                            return;
                        let e = 2;
                        const t = Boolean(a.rawData[3]);
                        return t ? {
                            _obj: "channelMixer",
                            gray: {
                                red: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                green: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                blue: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                constant: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 4)
                                },
                                _obj: "channelMatrix"
                            },
                            monochromatic: t
                        } : {
                            _obj: "channelMixer",
                            red: {
                                red: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                green: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                blue: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                constant: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 4)
                                },
                                _obj: "channelMatrix"
                            },
                            green: {
                                red: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                green: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                blue: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                constant: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 4)
                                },
                                _obj: "channelMatrix"
                            },
                            blue: {
                                red: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                green: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                blue: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 2)
                                },
                                constant: {
                                    _unit: "percentUnit",
                                    _value: a.rawData.readInt16BE(e += 4)
                                },
                                _obj: "channelMatrix"
                            },
                            monochromatic: t
                        }
                    }
                    async _getPosterize() {
                        const a = await this._getAdjustment();
                        if (a)
                            return {
                                _obj: "posterization",
                                levels: a.rawData.readInt16LE(1)
                            }
                    }
                    async _getThreshold() {
                        const a = await this._getAdjustment();
                        if (a)
                            return {
                                _obj: "thresholdClassEvent",
                                level: a.rawData.readInt16LE(1)
                            }
                    }
                    async _getSelectiveColor() {
                        const a = await this._getAdjustment();
                        if (!a)
                            return;
                        const e = {
                            _obj: "selectiveColor",
                            method: {
                                _enum: "correctionMethod",
                                _value: 1 === a.rawData.readInt16BE(2) ? "absolute" : "relative"
                            },
                            colorCorrection: []
                        };
                        let t = 12;
                        function n() {
                            const e = a.rawData.readInt16BE(t);
                            return t += 2,
                            {
                                _unit: "percentUnit",
                                _value: e
                            }
                        }
                        return ["radius", "yellows", "graininess", "cyans", "blues", "magenta", "whites", "neutrals", "blacks"].forEach((a=>{
                            e.colorCorrection.push({
                                _obj: "colorCorrection",
                                colors: {
                                    _enum: "colors",
                                    _value: a
                                },
                                cyan: n(),
                                magenta: n(),
                                yellowColor: n(),
                                black: n()
                            })
                        }
                        )),
                        e
                    }
                    async _getGradientMap() {
                        const a = await this._getAdjustment();
                        if (!a)
                            return;
                        const e = Boolean(a.rawData.readInt8(2))
                          , t = Boolean(a.rawData.readInt8(3))
                          , n = 2 * a.rawData[7];
                        let i = 12 + n;
                        const s = a.rawData.readInt16LE(9 + n)
                          , l = [];
                        for (var c = 0; c < s; c++) {
                            let e = i;
                            const t = a.rawData.readInt16BE(e)
                              , n = a.rawData.readInt16LE(e += 5)
                              , r = a.rawData[e += 3]
                              , s = a.rawData[e += 2]
                              , o = a.rawData[e += 2];
                            l.push(this._newGradientMapColor(t, n, r, s, o)),
                            i += 20
                        }
                        const u = a.rawData.readInt16LE(i - 1);
                        i += 2;
                        const d = [];
                        for (c = 0; c < u; c++) {
                            let e = i;
                            const t = a.rawData.readInt16BE(e)
                              , n = a.rawData.readInt16LE(e += 5)
                              , r = a.rawData.readInt16LE(e += 2) / 255 * 100;
                            d.push(this._newGradientTransparency(t, n, r)),
                            i += 10
                        }
                        const y = a.rawData.readInt16BE(i)
                          , m = Boolean(a.rawData.readInt16BE(i += 4)) ? "colorNoise" : "customStops"
                          , h = function(a, e) {
                            return a[e] << 24 | a[e + 1] << 16 | a[e + 2] << 8 | a[e + 3]
                        }(a.rawData, i += 2)
                          , w = Boolean(a.rawData.readInt16BE(i += 4))
                          , g = Boolean(a.rawData.readInt16BE(i += 2))
                          , _ = a.rawData.readInt16BE(i += 4)
                          , p = a.rawData.readInt16BE(i += 2)
                          , j = {
                            _enum: "colorSpace",
                            _value: r.find((a=>a.code === p)).name
                        };
                        function v() {
                            function e(e) {
                                return Math.round(o(a.rawData, e) / 32768 * 100)
                            }
                            return [e(i), e(i += 2), e(i += 2), e(i += 2)]
                        }
                        i += 2;
                        const L = v();
                        return i += 2,
                        {
                            _obj: "gradientMapClass",
                            dither: t,
                            reverse: e,
                            gradient: {
                                _obj: "gradientClassEvent",
                                gradientForm: {
                                    _enum: "gradientForm",
                                    _value: m
                                },
                                interfaceIconFrameDimmed: y,
                                colors: l,
                                transparency: d,
                                showTransparency: w,
                                vectorColor: g,
                                colorSpace: j,
                                smoothness: _,
                                randomSeed: h,
                                minimum: L,
                                maximum: v()
                            }
                        }
                    }
                    _newGradientMapColor(a, e, t, n, r) {
                        return {
                            _obj: "colorStop",
                            type: {
                                _enum: "colorStopType",
                                _value: "userStop"
                            },
                            location: a,
                            midpoint: e,
                            color: {
                                _obj: "RGBColor",
                                red: t,
                                grain: n,
                                blue: r
                            }
                        }
                    }
                    _newGradientTransparency(a, e, t) {
                        return {
                            _obj: "transferSpec",
                            location: a,
                            midpoint: e,
                            opacity: {
                                _unit: "percentUnit",
                                _value: t
                            }
                        }
                    }
                    _adjustByPercentage(a, e, t) {
                        return t / 100 * n.maxMin(a / t * 100 + e, 100, 0)
                    }
                    async _adjustGradientMapNoiseMinMax(a, e, t, n) {
                        const r = await this._getGradientMap();
                        if (!r)
                            return;
                        let i, s = r.gradient[a];
                        switch (r.gradient.colorSpace._value) {
                        case "RGBColor":
                            i = colorIndex.rgb.hsv([Math.round(2.55 * s[0]), Math.round(2.55 * s[1]), Math.round(2.55 * s[2])]),
                            i = this._adjustHSBColor(e, t, n, i);
                            const a = colorIndex.hsv.rgb(i);
                            s = [Math.round(a[0] / 255 * 100), Math.round(a[1] / 255 * 100), Math.round(a[2] / 255 * 100), s[3]];
                            break;
                        case "HSBColorEnum":
                            i = [Math.round(3.59 * s[0]), s[1], s[2]],
                            i = this._adjustHSBColor(e, t, n, i),
                            s = [Math.round(i[0] / 359 * 100), i[1], i[2], s[3]];
                            break;
                        case "labColor":
                            i = colorIndex.lab.hsv([s[0], Math.round(2.55 * s[1] - 128), Math.round(2.55 * s[2] - 128)]),
                            i = this._adjustHSBColor(e, t, n, i);
                            const r = colorIndex.hsv.lab(i);
                            s = [r[0], Math.round((r[1] + 128) / 255 * 100), Math.round((r[2] + 128) / 255 * 100), s[3]]
                        }
                        r.gradient[a] = s,
                        await this._modifyAdjustment(r)
                    }
                    _adjustHSBColor(a, e, t, n) {
                        const r = (n = colorInstance.adjustHSBColor(a, e, t, n))[0];
                        return n[0] = r < 0 ? 359 : r > 359 ? 0 : r,
                        n
                    }
                    async _getCurves() {
                        const a = await this._getAdjustment();
                        if (!a)
                            return;
                        const e = a.rawData;
                        if (Boolean(e[0]))
                            return;
                        function t(a, t) {
                            const n = [];
                            if (t) {
                                const a = o(e, r += 2);
                                for (let t = 0; t < a; t++) {
                                    const a = o(e, r += 2)
                                      , t = o(e, r += 2);
                                    n.push({
                                        _obj: "paint",
                                        horizontal: t,
                                        vertical: a
                                    })
                                }
                            } else
                                n.push({
                                    _obj: "paint",
                                    horizontal: 0,
                                    vertical: 0
                                }, {
                                    _obj: "paint",
                                    horizontal: 255,
                                    vertical: 255
                                });
                            return {
                                _obj: "curvesAdjustment",
                                channel: {
                                    _ref: "channel",
                                    _enum: "channel",
                                    _value: a
                                },
                                curve: n
                            }
                        }
                        const n = {
                            _obj: "curves",
                            presetKind: {
                                _enum: "presetKindType",
                                _value: "presetKindCustom"
                            },
                            adjustment: []
                        };
                        let r = 0;
                        const i = o(e, r += 5);
                        return n.adjustment.push(t("composite", Boolean(1 & i))),
                        n.adjustment.push(t("red", Boolean(2 & i))),
                        n.adjustment.push(t("grain", Boolean(4 & i))),
                        n.adjustment.push(t("blue", Boolean(8 & i))),
                        n
                    }
                    _getColorBalance(a) {
                        let e = 0;
                        return {
                            shadows: {
                                cyanRed: a.readInt16BE(e),
                                magentaGreen: a.readInt16BE(e += 2),
                                yellowBlue: a.readInt16BE(e += 2)
                            },
                            midtones: {
                                cyanRed: a.readInt16BE(e += 2),
                                magentaGreen: a.readInt16BE(e += 2),
                                yellowBlue: a.readInt16BE(e += 2)
                            },
                            highlights: {
                                cyanRed: a.readInt16BE(e += 2),
                                magentaGreen: a.readInt16BE(e += 2),
                                yellowBlue: a.readInt16BE(e += 2)
                            },
                            preserveLuminosity: Boolean(a[e += 2])
                        }
                    }
                    async _getHueSaturation() {
                        const a = await this._getAdjustment();
                        if (!a)
                            return;
                        const e = a.rawData
                          , t = {
                            _obj: "hueSaturation",
                            colorize: Boolean(e[2]),
                            adjustment: []
                        };
                        let n = 0;
                        t.colorize ? (n = 4,
                        t.adjustment.push({
                            _obj: "hueSatAdjustmentV2",
                            hue: Boolean(e[4]) ? 104 + e[5] : e[5],
                            saturation: e.readInt16BE(n += 2),
                            lightness: e.readInt16BE(n += 2)
                        }),
                        n = 16) : (n = 10,
                        t.adjustment.push({
                            _obj: "hueSatAdjustmentV2",
                            hue: e.readInt16BE(n),
                            saturation: e.readInt16BE(n += 2),
                            lightness: e.readInt16BE(n += 2)
                        }),
                        n = 16);
                        for (var r = 1; r <= 6; r++)
                            t.adjustment.push((i = n,
                            {
                                _obj: "hueSatAdjustmentV2",
                                localRange: r,
                                beginRamp: e.readInt16BE(i),
                                beginSustain: e.readInt16BE(i += 2),
                                endSustain: e.readInt16BE(i += 2),
                                endRamp: e.readInt16BE(i += 2),
                                hue: e.readInt16BE(i += 2),
                                saturation: e.readInt16BE(i += 2),
                                lightness: e.readInt16BE(i += 2)
                            })),
                            n += 14;
                        var i;
                        return t
                    }
                }
                function o(a, e) {
                    return a[e] << 8 | a[e + 1]
                }
                e.H = s.Instance()
            }
            ,
            917: (a,e,t)=>{
                const n = t(770)
                  , r = ["normal", "dissolve", "behind", "clearEnum", "darken", "multiply", "colorBurn", "linearBurn", "darkerColor", "lighten", "screen", "colorDodge", "linearDodge", "lighterColor", "overlay", "softLight", "hardLight", "vividLight", "linearLight", "pinLight", "hardMix", "difference", "exclusion", "blendSubtraction", "blendDivide", "hue", "saturation", "color", "luminosity"]
                  , i = ["normal", "dissolve", "darken", "multiply", "colorBurn", "linearBurn", "lighten", "screen", "colorDodge", "linearDodge", "overlay", "softLight", "hardLight", "vividLight", "linearLight", "pinLight", "hardMix", "difference", "exclusion", "blendSubtraction", "blendDivide"]
                  , s = ["normal", "pinLight", "multiply", "screen", "darken", "lighten", "color", "luminosity"]
                  , o = ["normal", "pinLight", "multiply", "screen", "darken", "lighten"]
                  , l = ["normal", "darken", "lighten", "hue", "saturation", "color", "luminosity"];
                class c {
                    constructor() {}
                    static Instance() {
                        return this._instance || (this._instance = new c),
                        this._instance
                    }
                    async getBrushSettings() {
                        const a = await this._getCurrentToolProperties();
                        if (!a || !a.currentToolOptions)
                            return;
                        const e = a.currentToolOptions;
                        let t, n, r, i, s;
                        return e.brush && (t = e.brush.diameter ? e.brush.diameter._value : void 0,
                        n = e.brush.hardness ? e.brush.hardness._value : void 0,
                        r = e.brush.angle ? e.brush.angle._value : void 0,
                        i = e.brush.roundness ? e.brush.roundness._value : void 0,
                        s = e.brush.spacing ? e.brush.spacing._value : void 0),
                        {
                            opacity: e.opacity,
                            flow: e.flow,
                            smooth: e.smooth,
                            pressure: e.pressure,
                            diameter: t,
                            hardness: n,
                            angle: r,
                            roundness: i,
                            spacing: s
                        }
                    }
                    async modifyBrush(a, e) {
                        const t = await this._getCurrentToolProperties();
                        t && await this._changeBrushSettings(a, e, t)
                    }
                    async _changeBrushSettings(a, e, t) {
                        switch (a) {
                        case "mode":
                            await this._changeToolMode(e, t);
                            break;
                        case "modeByKey":
                            await this._changeToolModeByKey(e, t);
                            break;
                        case "opacity":
                            await this._changeToolOpacity(e, t);
                            break;
                        case "flow":
                            await this._changeToolFlow(e, t);
                            break;
                        case "smooth":
                            await this._changeToolSmooth(e, t);
                            break;
                        case "pressure":
                            await this._changeToolPressure(e, t);
                            break;
                        case "diameter":
                            await this._changeBrushDiameter(e, t);
                            break;
                        case "hardness":
                            await this._changeBrushHardness(e, t);
                            break;
                        case "angle":
                            await this._changeBrushAngle(e, t);
                            break;
                        case "roundness":
                            await this._changeBrushRoudness(e, t);
                            break;
                        case "spacing":
                            await this._changeBrushSpacing(e, t);
                            break;
                        case "flipx":
                            await this._toggleBrushFlipX(t);
                            break;
                        case "flipy":
                            await this._toggleBrushFlipY(t)
                        }
                    }
                    async _changeToolModeByKey(a, e) {
                        const t = e.currentToolOptions.mode._value
                          , n = e.tool._enum
                          , c = await this._getLayerKind();
                        let u = "adjustmentLayer" === c ? i : r;
                        "blurTool" === n || "smudgeTool" === n || "artBrushTool" === n ? u = "adjustmentLayer" === c ? ["normal", "darken", "lighten"] : l : "spotHealingBrushTool" !== n && "magicStampTool" !== n || (u = "adjustmentLayer" === c ? o : s),
                        -1 !== u.indexOf(t) && await this._setToolOptions({
                            _obj: "null",
                            mode: {
                                _enum: "blendMode",
                                _value: a
                            }
                        }, e)
                    }
                    async _changeToolMode(a, e) {
                        const t = e.currentToolOptions.mode._value
                          , n = e.tool._enum
                          , c = await this._getLayerKind();
                        let u = "adjustmentLayer" === c ? i : r;
                        "blurTool" === n || "smudgeTool" === n || "artBrushTool" === n ? u = "adjustmentLayer" === c ? ["normal", "darken", "lighten"] : l : "spotHealingBrushTool" !== n && "magicStampTool" !== n || (u = "adjustmentLayer" === c ? o : s);
                        let d = 0
                          , y = u.indexOf(t);
                        -1 !== y && (0 === a ? d = 0 : (d = a < 0 ? y + 1 : y - 1,
                        d >= u.length && (d = 0),
                        d < 0 && (d = u.length - 1)),
                        await this._setToolOptions({
                            _obj: "null",
                            mode: {
                                _enum: "blendMode",
                                _value: u[d]
                            }
                        }, e))
                    }
                    async _changeToolOpacity(a, e) {
                        if (void 0 === e.currentToolOptions.opacity)
                            return;
                        let t = 100;
                        0 !== a && (t = this._adjustBrushValue(e.currentToolOptions.opacity, a, 0, 100)),
                        await this._setToolOptions({
                            opacity: t
                        }, e)
                    }
                    async _changeToolFlow(a, e) {
                        if (void 0 === e.currentToolOptions.flow)
                            return;
                        let t = 100;
                        0 !== a && (t = this._adjustBrushValue(e.currentToolOptions.flow, a, 0, 100)),
                        await this._setToolOptions({
                            flow: t
                        }, e)
                    }
                    async _changeToolSmooth(a, e) {
                        if (void 0 === e.currentToolOptions.smooth)
                            return;
                        let t = 100;
                        0 !== a && (t = this._adjustBrushValue(e.currentToolOptions.smooth, a, 0, 100)),
                        await this._setToolOptions({
                            smooth: t,
                            smoothingValue: Math.round(t / 100 * 255)
                        }, e)
                    }
                    async _changeToolPressure(a, e) {
                        if (void 0 === e.currentToolOptions.pressure)
                            return;
                        let t = 100;
                        0 !== a && (t = this._adjustBrushValue(e.currentToolOptions.pressure, a, 0, 100)),
                        await this._setToolOptions({
                            pressure: t
                        }, e)
                    }
                    async _changeBrushDiameter(a, e) {
                        const t = e.currentToolOptions.brush;
                        if (void 0 === t.diameter)
                            return;
                        let r = 25;
                        if (0 !== a) {
                            const e = .03;
                            a = Math.ceil(t.diameter._value * e) * n.maxMin(a, 5, -5),
                            r = this._adjustBrushValue(t.diameter._value, a, 1, 5e3)
                        }
                        await this._setBrushOptions({
                            masterDiameter: {
                                _unit: "pixelsUnit",
                                _value: r
                            }
                        })
                    }
                    async _changeBrushHardness(a, e) {
                        const t = e.currentToolOptions.brush;
                        if (void 0 === t.hardness)
                            return;
                        let n = 100;
                        0 !== a && (n = this._adjustBrushValue(t.hardness._value, a, 0, 100)),
                        t.hardness._value = n,
                        await this._setBrushOptions(t)
                    }
                    async _changeBrushAngle(a, e) {
                        const t = e.currentToolOptions.brush;
                        if (void 0 === t.angle)
                            return;
                        let n = 100;
                        0 !== a && (n = t.angle._value + a),
                        t.angle._value = n,
                        await this._setBrushOptions(t)
                    }
                    async _changeBrushRoudness(a, e) {
                        const t = e.currentToolOptions.brush;
                        if (void 0 === t.roundness)
                            return;
                        let n = 100;
                        0 !== a && (n = this._adjustBrushValue(t.roundness._value, a, 1, 100)),
                        t.roundness._value = n,
                        await this._setBrushOptions(t)
                    }
                    async _changeBrushSpacing(a, e) {
                        const t = e.currentToolOptions.brush;
                        if (void 0 === t.spacing)
                            return;
                        let n = 100;
                        0 !== a && (n = this._adjustBrushValue(t.spacing._value, a, 1, 1e3)),
                        t.spacing._value = n,
                        await this._setBrushOptions(t)
                    }
                    async _toggleBrushFlipX(a) {
                        const e = a.currentToolOptions.brush;
                        void 0 !== e.flipX && (e.flipX = !e.flipX,
                        await this._setBrushOptions(e))
                    }
                    async _toggleBrushFlipY(a) {
                        const e = a.currentToolOptions.brush;
                        void 0 !== e.flipY && (e.flipY = !e.flipY,
                        await this._setBrushOptions(e))
                    }
                    _adjustBrushValue(a, e, t, n) {
                        const r = a + e;
                        return Math.min(n, Math.max(t, r))
                    }
                    async _getLayerKind() {
                        switch ((await n.executeBatchPlay({
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "layerKind"
                                }, {
                                    _ref: "layer",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }))[0].layerKind) {
                        case 1:
                            return "layer";
                        case 2:
                            return "adjustmentLayer";
                        case 3:
                            return "text";
                        case 4:
                            return "shape";
                        case 5:
                            return "smartObject";
                        case 7:
                            return "group";
                        case 12:
                            return "background"
                        }
                    }
                    _getToolOptionsToDescriptor(a) {
                        const e = {};
                        return Object.keys(a).forEach((t=>{
                            const n = a[t]
                              , r = typeof n;
                            "function" != r && "object" != r && (e[t] = n)
                        }
                        )),
                        e
                    }
                    async _setToolOptions(a, e) {
                        a._obj = "null";
                        const t = {
                            _obj: "set",
                            _target: {
                                _ref: e.tool._enum
                            },
                            to: Object.assign(this._getToolOptionsToDescriptor(e.currentToolOptions), a),
                            _options: {
                                dialogOptions: "silent"
                            }
                        };
                        await n.executeBatchPlay(t)
                    }
                    async _setBrushOptions(a) {
                        a._obj = "brush";
                        const e = {
                            _obj: "set",
                            _target: {
                                _ref: "brush",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            to: a,
                            _options: {
                                dialogOptions: "silent"
                            }
                        };
                        await n.executeBatchPlay(e)
                    }
                    async _getCurrentToolProperties() {
                        return (await n.executeBatchPlay({
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "currentToolOptions"
                                }, {
                                    _ref: "application",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }))[0]
                    }
                }
                e.brushInstance = c.Instance()
            }
            ,
            307: (a,e,t)=>{
                var n = t(873);
                const r = t(480).a
                  , i = t(271).b
                  , s = t(770);
                a.exports = class {
                    constructor(a) {
                        this._communicationService = a,
                        this._photoshopCommands = new n(a)
                    }
                    async handleCommand(a) {
                        try {
                            switch (a.tn) {
                            case "undo":
                                await this._undo();
                                break;
                            case "redo":
                                await this._redo();
                                break;
                            case "setHistoryState":
                                await this._photoshopCommands.setHistoryState(a.args, a.incs),
                                await this._sendLayerInfo();
                                break;
                            case "getActionsRequest":
                                const e = r.getActions();
                                this._communicationService.send({
                                    type: "getActionsResponse",
                                    payload: `${e.join(",")}`
                                });
                                break;
                            case "getLayerInfoRequest":
                                await this._sendLayerInfo();
                                break;
                            default:
                                await this._handleCommand(a)
                            }
                        } catch (a) {
                            if (!a.message || "The command failed because Photoshop is in a modal state" !== a.message)
                                throw a;
                            await s.wait(10)
                        }
                    }
                    async _sendLayerInfo() {
                        const a = await i.getLayerInfo();
                        this._communicationService.send({
                            type: "getLayerInfoResponse",
                            payload: JSON.stringify(a)
                        })
                    }
                    async _undo() {
                        await r.setHistoryState(-1),
                        await this._sendLayerInfo()
                    }
                    async _redo() {
                        await r.setHistoryState(1),
                        await this._sendLayerInfo()
                    }
                    async _handleCommand(a) {
                        await this._photoshopCommands[a.tn](a.args, a.incs)
                    }
                }
            }
            ,
            480: (a,e,t)=>{
                const n = t(192).app
                  , r = t(192).action
                  , i = t(770);
                class s {
                    constructor() {
                        this._currentTool = n.currentTool.id,
                        r.addNotificationListener([{
                            event: "select"
                        }], ((a,e)=>{
                            this._onSelectEvent(a, e)
                        }
                        ))
                    }
                    static Instance() {
                        return this._instance || (this._instance = new s),
                        this._instance
                    }
                    async getHistoryState() {
                        return (await i.executeBatchPlay)({
                            _obj: "get",
                            _target: [{
                                _ref: "historyState",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }]
                        })[0]
                    }
                    async setHistoryState(a) {
                        const e = await this.getHistoryState()
                          , t = i.maxMin(e.itemIndex + a, e.count, 1);
                        await i.executeBatchPlay({
                            _obj: "select",
                            _target: {
                                _ref: "historyState",
                                _index: t
                            }
                        })
                    }
                    async executePSAction(a) {
                        try {
                            let e = a.split(":")
                              , t = e[1]
                              , r = e[2]
                              , i = n.actionTree.find((a=>a.name === t)).actions.find((a=>a.name === r));
                            await i.play()
                        } catch {}
                    }
                    async setTool(a) {
                        let e = n.currentTool;
                        await i.executeBatchPlay({
                            _obj: "select",
                            _target: {
                                _ref: a
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        }),
                        this._prevTool = e.id,
                        this._currentTool = n.currentTool.id
                    }
                    async setPrevTool() {
                        this._prevTool && await this.setTool(this._prevTool)
                    }
                    async activateFreeTransform() {
                        await i.executeBatchPlay({
                            _obj: "select",
                            _target: {
                                _ref: "menuItemClass",
                                _enum: "menuItemType",
                                _value: "freeTransform"
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    getActions() {
                        let a = [];
                        return n.actionTree.forEach((e=>{
                            e.name && 0 !== e.actions.length && e.actions.forEach((t=>{
                                a.push(`${e.name}:${t.name}`)
                            }
                            ))
                        }
                        )),
                        a
                    }
                    async applyStroke() {
                        await i.executeBatchPlay({
                            _obj: "stroke",
                            width: 1,
                            location: {
                                _enum: "strokeLength",
                                _value: "center"
                            },
                            opacity: {
                                _unit: "percentUnit",
                                _value: 100
                            },
                            mode: {
                                _enum: "blendMode",
                                _value: "normal"
                            },
                            color: {
                                _obj: "CMYKColorClass",
                                cyan: 0,
                                magenta: 54.01,
                                yellowColor: 72,
                                black: 0
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async rotateCanvas(a) {
                        await i.executeBatchPlay({
                            _obj: "rotateEventEnum",
                            _target: {
                                _enum: "ordinal",
                                _ref: "document",
                                _value: "first"
                            },
                            angle: {
                                _unit: "angleUnit",
                                _value: a
                            }
                        })
                    }
                    _onSelectEvent(a, e) {
                        let t = e._target[0]._ref;
                        if (t && t.includes("Tool")) {
                            if (this._currentTool === t)
                                return;
                            this._prevTool = this._currentTool,
                            this._currentTool = t
                        }
                    }
                }
                e.a = s.Instance()
            }
            ,
            271: (a,e,t)=>{
                const n = t(192).app
                  , r = t(192).action
                  , i = t(192).core
                  , s = "onActiveLayerChangedKey"
                  , o = t(770)
                  , l = t(19).H;
                var c = t(598);
                const u = ["normal", "dissolve", "darken", "multiply", "colorBurn", "linearBurn", "darkerColor", "lighten", "screen", "colorDodge", "linearDodge", "lighterColor", "overlay", "softLight", "hardLight", "vividLight", "linearLight", "pinLight", "hardMix", "difference", "exclusion", "blendSubtraction", "blendDivide", "hue", "saturation", "color", "luminosity"];
                var d;
                !function(a) {
                    a[a.any = 0] = "any",
                    a[a.pixel = 1] = "pixel",
                    a[a.adjustment = 2] = "adjustment",
                    a[a.text = 3] = "text",
                    a[a.vector = 4] = "vector",
                    a[a.smartObject = 5] = "smartObject",
                    a[a.video = 6] = "video",
                    a[a.group = 7] = "group",
                    a[a.threeD = 8] = "threeD",
                    a[a.gradient = 9] = "gradient",
                    a[a.pattern = 10] = "pattern",
                    a[a.solidColor = 11] = "solidColor",
                    a[a.background = 12] = "background",
                    a[a.groupEnd = 13] = "groupEnd"
                }(d || (d = {}));
                const y = ["normal", "dissolve", "darken", "multiply", "colorBurn", "linearBurn", "darkerColor", "lighten", "screen", "colorDodge", "linearDodge", "lighterColor", "overlay", "softLight", "hardLight", "vividLight", "linearLight", "pinLight", "hardMix", "difference", "exclusion", "blendSubtraction", "blendDivide", "hue", "saturation", "color", "luminosity"];
                class m {
                    constructor() {
                        this._activeLayerChanged = new c,
                        r.addNotificationListener([{
                            event: "select"
                        }], ((a,e)=>{
                            this._onSelect(e)
                        }
                        )),
                        r.addNotificationListener([{
                            event: "make"
                        }, {
                            event: "delete"
                        }, {
                            event: "open"
                        }, {
                            event: "gaussianBlur"
                        }, {
                            event: "boxBlur"
                        }, {
                            event: "highPass"
                        }, {
                            event: "move"
                        }, {
                            event: "$Avrg"
                        }, {
                            event: "blurEvent"
                        }, {
                            event: "blurMore"
                        }, {
                            event: "clouds"
                        }, {
                            event: "despeckle"
                        }, {
                            event: "sharpen"
                        }, {
                            event: "sharpenEdges"
                        }, {
                            event: "sharpenMore"
                        }, {
                            event: "close"
                        }, {
                            event: "newPlacedLayer"
                        }, {
                            event: "rasterizeLayer"
                        }, {
                            event: "placedLayerConvertToLayers"
                        }], ((a,e)=>{
                            this._onActiveLayerChanged()
                        }
                        )),
                        r.addNotificationListener([{
                            event: "move"
                        }], ((a,e)=>{
                            Array.isArray(e.to._ref) && e.to._ref.some((a=>"filterFX" === a._ref)) && this._onActiveLayerChanged()
                        }
                        )),
                        r.addNotificationListener([{
                            event: "modalStateChanged"
                        }], ((a,e)=>{
                            "Gradient Editor" === e.title && "exit" === e.state._value && 0 === e.level && this._onActiveLayerChanged()
                        }
                        )),
                        r.addNotificationListener([{
                            event: "invokeCommand"
                        }], ((a,e)=>{
                            101 !== e.commandID && 132 !== e.commandID || this._onActiveLayerChanged()
                        }
                        ))
                    }
                    static Instance() {
                        return this._instance || (this._instance = new m),
                        this._instance
                    }
                    activeLayerChangedSubscribe(a) {
                        this._activeLayerChanged.subscribe(s, a)
                    }
                    async removeBackground() {
                        await o.executeBatchPlay({
                            _obj: "removeBackground"
                        })
                    }
                    async selectSubject() {
                        await o.executeBatchPlay({
                            _obj: "autoCutout",
                            sampleAllLayers: !1
                        })
                    }
                    async deleteUserMask() {
                        const a = (await o.executeBatchPlay({
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "hasUserMask"
                                }, {
                                    _ref: "layer",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }))[0];
                        a && a.hasUserMask && await o.executeBatchPlay({
                            _obj: "delete",
                            _target: {
                                _ref: "channel",
                                _enum: "channel",
                                _value: "mask"
                            }
                        })
                    }
                    async deleteVectorMask() {
                        const a = (await o.executeBatchPlay({
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "hasVectorMask"
                                }, {
                                    _ref: "layer",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }))[0];
                        a && a.hasVectorMask && await o.executeBatchPlay({
                            _obj: "delete",
                            _target: [{
                                _ref: "path",
                                _enum: "path",
                                _value: "vectorMask"
                            }, {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }]
                        })
                    }
                    async selectLayer(a) {
                        const e = (await o.executeBatchPlay({
                            _obj: "multiGet",
                            _target: {
                                _ref: "document",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            extendedReference: [["numberOfLayers", "targetLayersIndexes"]]
                        }))[0];
                        e.targetLayersIndexes.length > 0 && ("backwardEnum" === a && 0 === e.targetLayersIndexes[0]._index || "forwardEnum" === a && e.targetLayersIndexes[e.targetLayersIndexes.length - 1]._index === e.numberOfLayers) || await o.executeBatchPlay({
                            _obj: "select",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: a
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async changeBlendMode(a) {
                        const e = (await o.executeBatchPlay({
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "mode"
                                }, {
                                    _ref: "layer",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }))[0].mode._value
                          , t = y.indexOf(e);
                        if (t < 0)
                            return;
                        let n = 0;
                        a > 0 ? n = t + 1 : a < 0 && (n = t - 1),
                        n >= y.length && (n = 0),
                        n < 0 && (n = y.length - 1),
                        await o.executeBatchPlay({
                            _obj: "set",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            to: {
                                _obj: "layer",
                                mode: {
                                    _enum: "blendMode",
                                    _value: y[n]
                                }
                            }
                        })
                    }
                    async setBlendModeLoop(a) {
                        const e = await this._getLayerMode();
                        let t = 0
                          , n = u.indexOf(e);
                        -1 !== n && (0 === a ? t = 0 : (t = a < 0 ? n + 1 : n - 1,
                        t >= u.length && (t = 0),
                        t < 0 && (t = u.length - 1)),
                        await this.setBlendMode(u[t]))
                    }
                    async _getLayerMode() {
                        return (await o.executeBatchPlay({
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "mode"
                                }, {
                                    _ref: "layer",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }))[0].mode._value
                    }
                    async setBlendMode(a) {
                        await o.executeBatchPlay({
                            _obj: "set",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            to: {
                                _obj: "layer",
                                mode: {
                                    _enum: "blendMode",
                                    _value: a
                                }
                            }
                        })
                    }
                    async setLayerFill(a, e) {
                        const t = (await o.executeBatchPlay({
                            _obj: "multiGet",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            extendedReference: [["visible", "layerLocking", "fillOpacity"]]
                        }))[0];
                        if (!t.visible || t.layerLocking.protectAll)
                            return;
                        let n = a;
                        e && (n = Math.round(t.fillOpacity / 255 * 100),
                        n = o.maxMin(n + a, 100, 0)),
                        await o.executeBatchPlay({
                            _obj: "set",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            to: {
                                _obj: "layer",
                                fillOpacity: n
                            }
                        })
                    }
                    async setLayerOpacity(a, e) {
                        const t = (await o.executeBatchPlay({
                            _obj: "multiGet",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            extendedReference: [["visible", "layerLocking", "opacity"]]
                        }))[0];
                        if (!t.visible || t.layerLocking.protectAll)
                            return;
                        let n = a;
                        e && (n = Math.round(t.opacity / 255 * 100),
                        n = o.maxMin(n + a, 100, 0)),
                        await o.executeBatchPlay({
                            _obj: "set",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            to: {
                                _obj: "layer",
                                opacity: n
                            }
                        })
                    }
                    async createLayer() {
                        await o.executeBatchPlay({
                            _obj: "make",
                            _target: {
                                _ref: "layer"
                            }
                        })
                    }
                    async deleteLayer() {
                        await o.executeBatchPlay({
                            _obj: "delete",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }
                        })
                    }
                    async getLayerName() {
                        return (await o.executeBatchPlay({
                            _obj: "get",
                            _target: [{
                                _property: "name"
                            }, {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }]
                        }))[0].name
                    }
                    async isolateLayer() {
                        await o.executeBatchPlay({
                            _obj: "show",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            toggleOptionsPalette: !0,
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async moveLayer(a) {
                        await o.executeBatchPlay({
                            _obj: "move",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            to: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: a
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async copyMergeVisible() {
                        await o.executeBatchPlay({
                            _obj: "mergeVisible",
                            duplicate: !0
                        })
                    }
                    async mergeVisible() {
                        await o.executeBatchPlay({
                            _obj: "mergeVisible"
                        })
                    }
                    async copyMerged() {
                        await o.executeBatchPlay({
                            _obj: "mergeLayersNew",
                            duplicate: !0,
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async setFill(a) {
                        const e = a ? "foregroundColor" : "backgroundColor";
                        await o.executeBatchPlay({
                            _obj: "fill",
                            using: {
                                _enum: "fillContents",
                                _value: e
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async mergeDown() {
                        await o.executeBatchPlay({
                            _obj: "mergeLayersNew",
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async duplicate() {
                        await o.executeBatchPlay({
                            _obj: "duplicate",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async contentAwareFill() {
                        await o.executeBatchPlay({
                            _obj: "fill",
                            using: {
                                _enum: "fillContents",
                                _value: "contentAware"
                            },
                            contentAwareColorAdaptationFill: !0,
                            contentAwareRotateFill: !1,
                            contentAwareScaleFill: !1,
                            contentAwareMirrorFill: !1,
                            opacity: {
                                _unit: "percentUnit",
                                _value: 100
                            },
                            mode: {
                                _enum: "blendMode",
                                _value: "normal"
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async createLayerMask(a) {
                        await this._createLayerMask(a ? "hideAll" : "revealAll")
                    }
                    async createLayerMaskFromSelection() {
                        await this._createLayerMask("revealSelection")
                    }
                    async toggleLayerMaskSelection() {
                        const a = await r.batchPlay([{
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "hasUserMask"
                                }, {
                                    _ref: "layer",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }, {
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "channelName"
                                }, {
                                    _ref: "channel",
                                    _enum: "channel",
                                    _value: "mask"
                                }]
                            }
                        }, {
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "channelName"
                                }, {
                                    _ref: "channel",
                                    _enum: "channel",
                                    _value: "targetEnum"
                                }]
                            }
                        }], {
                            dialogOptions: "silent",
                            synchronousExecution: !1
                        })
                          , e = a[0].hasUserMask
                          , t = a[1].channelName
                          , n = a[2].channelName;
                        if (!e)
                            return;
                        const i = t === n ? "RGB" : "mask";
                        await o.executeBatchPlay({
                            _obj: "select",
                            _target: {
                                _enum: "channel",
                                _ref: "channel",
                                _value: i
                            }
                        })
                    }
                    async layerVisibleToggle() {
                        const a = n.activeDocument.activeLayers[0];
                        a.visible = !a.visible
                    }
                    async clippingMaskToggle() {
                        await i.performMenuCommand({
                            commandID: 2972
                        })
                    }
                    async groupLayers() {
                        return await o.executeBatchPlay({
                            _obj: "make",
                            _target: {
                                _ref: "layerSection"
                            },
                            from: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        }),
                        n.activeDocument.activeLayers[0]
                    }
                    async smartObjectToggle() {
                        const a = n.activeDocument.activeLayers;
                        1 === a.length && a[0].kind === d.smartObject ? r.batchPlay([{
                            _obj: "placedLayerConvertToLayers"
                        }, {
                            _obj: "ungroupLayersEvent",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }
                        }], {
                            synchronousExecution: !0,
                            historyStateInfo: {
                                target: {
                                    _ref: "document",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                },
                                name: "Unwrap Smart Object"
                            }
                        }) : await o.executeBatchPlay({
                            _obj: "newPlacedLayer",
                            _target: {
                                _ref: "layerSection"
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async toggleSelectedLayersLink() {
                        await o.executeBatchPlay({
                            _obj: "linkSelectedLayers",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async unlinkSelectedLayers() {
                        await o.executeBatchPlay({
                            _obj: "unlinkSelectedLayers",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async selectLinkedLayers() {
                        await o.executeBatchPlay({
                            _obj: "selectLinkedLayers",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async copyLayerStyle() {
                        await o.executeBatchPlay({
                            _obj: "copyEffects",
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async pasteLayerStyle() {
                        await o.executeBatchPlay({
                            _obj: "pasteEffects",
                            allowPasteFXOnLayerSet: !0,
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async clearLayerStyle() {
                        await o.executeBatchPlay({
                            _obj: "disableLayerStyle",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async getLayerInfo() {
                        const a = await r.batchPlay([{
                            _obj: "multiGet",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            extendedReference: [["hasFilterMask", "hasUserMask", "hasVectorMask", "layerKind", "layerLocking", "artboardEnabled"]]
                        }, {
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "adjustment"
                                }, {
                                    _ref: "adjustmentLayer",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }], {
                            synchronousExecution: !1,
                            dialogOptions: "silent"
                        });
                        if (null != a[0].message)
                            return;
                        const e = a[0]
                          , t = a[1].adjustment ? a[1].adjustment[0]._obj : "";
                        return e.smartObjectDetails = e.layerKind === d.smartObject ? await this._getSmartObjectDetails() : null,
                        e.adjustment = {
                            name: t,
                            details: await this._getAdjustmentLayerDetails(t)
                        },
                        e
                    }
                    async transformOffset(a, e) {
                        await o.executeBatchPlay({
                            _obj: "move",
                            _target: [{
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }],
                            to: {
                                _obj: "offset",
                                horizontal: {
                                    _unit: "pixelsUnit",
                                    _value: a
                                },
                                vertical: {
                                    _unit: "pixelsUnit",
                                    _value: e
                                }
                            }
                        })
                    }
                    async transformProportions(a, e) {
                        const t = 32e3;
                        function n(a) {
                            if (a > 50)
                                return 1;
                            var e = Math.log(1.1)
                              , t = (Math.log(20) - e) / -50;
                            return Math.exp(e + t * (a - 50))
                        }
                        const r = (await o.executeBatchPlay({
                            _obj: "multiGet",
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            },
                            extendedReference: [["bounds"]]
                        }))[0];
                        a = a * n(r.bounds.height._value) + 100,
                        e = e * n(r.bounds.width._value) + 100;
                        let i = r.bounds.width._value / 100 * e
                          , s = r.bounds.height._value / 100 * a;
                        (i > t || i < 4) && (e = o.maxMin(i, t, 4) / r.bounds.width._value * 100,
                        i = r.bounds.width._value / 100 * e),
                        (s > t || s < 4) && (a = o.maxMin(s, t, 4) / r.bounds.height._value * 100,
                        s = r.bounds.height._value / 100 * a);
                        const l = (i - r.bounds.width._value) / 2
                          , c = (s - r.bounds.height._value) / 2;
                        await o.executeBatchPlay({
                            _obj: "transform",
                            height: {
                                _unit: "percentUnit",
                                _value: a
                            },
                            width: {
                                _unit: "percentUnit",
                                _value: e
                            },
                            offset: {
                                _obj: "offset",
                                horizontal: {
                                    _unit: "pixelsUnit",
                                    _value: l
                                },
                                vertical: {
                                    _unit: "pixelsUnit",
                                    _value: c
                                }
                            },
                            freeTransformCenterState: {
                                _enum: "quadCenterState",
                                _value: "QCSAverage"
                            },
                            interfaceIconFrameDimmed: {
                                _enum: "interpolationType",
                                _value: "bicubic"
                            },
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }
                        })
                    }
                    async transformRotate(a) {
                        await o.executeBatchPlay({
                            _obj: "rotateEventEnum",
                            angle: {
                                _unit: "angleUnit",
                                _value: a
                            },
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }
                        })
                    }
                    async transformFlip(a) {
                        await o.executeBatchPlay({
                            _obj: "flip",
                            axis: {
                                _enum: "orientation",
                                _value: a
                            },
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }
                        })
                    }
                    async vectorMaskDensity(a) {
                        await this._maskDensity("vectorMaskDensity", a)
                    }
                    async vectorMaskFeather(a) {
                        await this._maskFeather("vectorMaskFeather", a)
                    }
                    async userMaskDensity(a) {
                        await this._maskDensity("userMaskDensity", a)
                    }
                    async userMaskFeather(a) {
                        await this._maskFeather("userMaskFeather", a)
                    }
                    async _maskDensity(a, e) {
                        const t = (await o.executeBatchPlay({
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: a
                                }, {
                                    _ref: "layer",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }))[0]
                          , n = Math.round(t[a] / 255 * 100);
                        e = o.maxMin(n + e, 100, 0);
                        const r = {
                            _obj: "set",
                            to: {
                                _obj: "layer"
                            },
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }
                        };
                        r.to[a] = {
                            _unit: "percentUnit",
                            _value: e
                        },
                        await o.executeBatchPlay(r)
                    }
                    async _maskFeather(a, e) {
                        const t = (await o.executeBatchPlay({
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: a
                                }, {
                                    _ref: "layer",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }))[0];
                        var n;
                        e = o.maxMin(t[a] + e / 10 * ((n = t[a]) < 10 ? 1 : n < 200 ? 10 : 100), 1e3, 0);
                        const r = {
                            _obj: "set",
                            to: {
                                _obj: "layer"
                            },
                            _target: {
                                _ref: "layer",
                                _enum: "ordinal",
                                _value: "targetEnum"
                            }
                        };
                        r.to[a] = {
                            _unit: "pixelsUnit",
                            _value: e
                        },
                        await o.executeBatchPlay(r)
                    }
                    _onSelect(a) {
                        Array.isArray(a._target) && a._target.some((a=>"layer" === a._ref || "document" === a._ref)) && this._onActiveLayerChanged()
                    }
                    async _onActiveLayerChanged() {
                        const a = await this.getLayerInfo();
                        this._activeLayerChanged.publish(s, a)
                    }
                    async _getAdjustmentLayerDetails(a) {
                        switch (a) {
                        case "gradientMapClass":
                            const a = await l.getGradientMap();
                            return a ? JSON.stringify({
                                colorsCount: a.gradient.colors.length,
                                transparencyCount: a.gradient.transparency.length,
                                gradientForm: a.gradient.gradientForm._value
                            }) : null;
                        case "curves":
                            const e = await l.getCurves();
                            return e ? JSON.stringify(e.adjustment.map((a=>({
                                channel: a.channel._value,
                                curves: a.curve.map((a=>({
                                    input: a.horizontal,
                                    output: a.vertical
                                })))
                            })))) : null;
                        default:
                            return null
                        }
                    }
                    async _getSmartObjectDetails() {
                        const a = await filtersInstance.getSmartObject();
                        return a.filterFX ? {
                            filters: a.filterFX.map((a=>({
                                name: a.filter ? a.filter._obj : a.name,
                                displayName: a.name
                            })))
                        } : {
                            filters: []
                        }
                    }
                    async _createLayerMask(a) {
                        await o.executeBatchPlay({
                            _obj: "make",
                            new: {
                                _class: "channel"
                            },
                            at: {
                                _ref: "channel",
                                _enum: "channel",
                                _value: "mask"
                            },
                            using: {
                                _enum: "userMaskEnabled",
                                _value: a
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                }
                e.b = m.Instance()
            }
            ,
            873: (a,e,t)=>{
                t(192).app,
                t(192).action;
                const n = t(192).core
                  , r = t(770)
                  , i = t(917).brushInstance
                  , s = t(480).a
                  , o = t(271).b
                  , l = t(116).q
                  , c = t(19).H;
                function u(a) {
                    return "true" === a.toLowerCase()
                }
                a.exports = class {
                    constructor(a) {
                        this._communicationService = a
                    }
                    async performMenuCommand(a, e) {
                        await n.performMenuCommand({
                            commandID: Number(a[0])
                        })
                    }
                    async modifySmartFilter(a, e) {
                        await filtersInstance.modifySmartFilter(a[0], e[0]),
                        await r.wait(60)
                    }
                    async smartfilterCreate(a, e) {
                        await filtersInstance.create(a[0]),
                        await this._sendLayerInfo()
                    }
                    async modifySmartFilterByIndex(a, e) {
                        await filtersInstance.modifySmartFilterByIndex(Number(a[0]), e[0]),
                        await r.wait(60)
                    }
                    async toggleSmartFilterVisibility(a, e) {
                        await filtersInstance.toggleFilterVisibility(Number(a[0]))
                    }
                    async forecolor(a, e) {
                        await colorInstance.colorAdjustment(e[0], e[1], e[2], !0)
                    }
                    async backcolor(a, e) {
                        await colorInstance.colorAdjustment(e[0], e[1], e[2], !1)
                    }
                    async forecolorH(a, e) {
                        await colorInstance.colorAdjustment(e[0], 0, 0, !0)
                    }
                    async forecolorS(a, e) {
                        await colorInstance.colorAdjustment(0, e[0], 0, !0)
                    }
                    async forecolorB(a, e) {
                        await colorInstance.colorAdjustment(0, 0, e[0], !0)
                    }
                    async backcolorH(a, e) {
                        await colorInstance.colorAdjustment(e[0], 0, 0, !1)
                    }
                    async backcolorS(a, e) {
                        await colorInstance.colorAdjustment(0, e[0], 0, !1)
                    }
                    async backcolorB(a, e) {
                        await colorInstance.colorAdjustment(0, 0, e[0], !1)
                    }
                    async forecolorSet(a, e) {
                        await colorInstance.colorSet(!0, a[0])
                    }
                    async backcolorSet(a, e) {
                        await colorInstance.colorSet(!1, a[0])
                    }
                    async colorReset(a, e) {
                        await colorInstance.colorSet(!0, "white"),
                        await colorInstance.colorSet(!1, "black")
                    }
                    async zoomInOut(a, e) {
                        await l.zoom(e[0]),
                        await r.wait(10)
                    }
                    async zoomToFit(a, e) {
                        await l.zoomToFit()
                    }
                    async modifyBrushSize(a, e) {
                        await i.modifyBrush("diameter", e[0]);
                        const t = await i.getBrushSettings();
                        this._communicationService.send({
                            type: "brushParametersUpdate",
                            payload: JSON.stringify(t)
                        })
                    }
                    async modifyBrushModeByKey(a, e) {
                        await i.modifyBrush("modeByKey", a[0])
                    }
                    async modifyBrushMode(a, e) {
                        await i.modifyBrush("mode", e[0])
                    }
                    async modifyBrushOpacity(a, e) {
                        await i.modifyBrush("opacity", e[0])
                    }
                    async modifyBrushFlow(a, e) {
                        await i.modifyBrush("flow", e[0])
                    }
                    async modifyBrushSmooth(a, e) {
                        await i.modifyBrush("smooth", e[0])
                    }
                    async modifyBrushPressure(a, e) {
                        await i.modifyBrush("pressure", e[0])
                    }
                    async modifyBrushHardness(a, e) {
                        await i.modifyBrush("hardness", e[0])
                    }
                    async modifyBrushAngle(a, e) {
                        await i.modifyBrush("angle", e[0])
                    }
                    async modifyBrushRoundness(a, e) {
                        await i.modifyBrush("roundness", e[0])
                    }
                    async modifyBrushSpacing(a, e) {
                        await i.modifyBrush("spacing", e[0])
                    }
                    async layerRemoveBackground(a, e) {
                        await o.removeBackground()
                    }
                    async layerSelectSubject(a, e) {
                        await o.selectSubject()
                    }
                    async selectLayer(a, e) {
                        await o.selectLayer(a[0]);
                        const t = await o.getLayerName();
                        this._communicationService.send({
                            type: "overlayMessage",
                            payload: `[${t}] Selected`
                        }),
                        await this._sendLayerInfo(),
                        await r.wait(20)
                    }
                    async changeBlendMode(a, e) {
                        await o.changeBlendMode(e[0])
                    }
                    async setLayerFill(a, e) {
                        await o.setLayerFill(e[0], u(a[0])),
                        await r.wait(30)
                    }
                    async setLayerOpacity(a, e) {
                        await o.setLayerOpacity(e[0], u(a[0])),
                        await r.wait(30)
                    }
                    async createLayer(a, e) {
                        await o.createLayer();
                        const t = await o.getLayerName();
                        this._communicationService.send({
                            type: "overlayMessage",
                            payload: `New Layer [${t}]`
                        }),
                        await this._sendLayerInfo()
                    }
                    async deleteLayer(a, e) {
                        const t = await o.getLayerName();
                        await o.deleteLayer(),
                        this._communicationService.send({
                            type: "overlayMessage",
                            payload: `Delete Layer [${t}]`
                        }),
                        await this._sendLayerInfo()
                    }
                    async isolateLayer(a, e) {
                        await o.isolateLayer();
                        const t = await o.getLayerName();
                        this._communicationService.send({
                            type: "overlayMessage",
                            payload: `Isolate Layer [${t}]`
                        })
                    }
                    async moveLayer(a, e) {
                        await o.moveLayer(a[0]);
                        const t = await o.getLayerName();
                        this._communicationService.send({
                            type: "overlayMessage",
                            payload: `Move Layer [${t}]`
                        })
                    }
                    async copyMergeVisible(a, e) {
                        await o.copyMergeVisible()
                    }
                    async copyMerge(a, e) {
                        await o.copyMerged()
                    }
                    async setFill(a, e) {
                        await o.setFill(u(a[0]))
                    }
                    async mergeDown(a, e) {
                        await o.mergeDown()
                    }
                    async duplicateLayer(a, e) {
                        await o.duplicate()
                    }
                    async contentAwareFill(a, e) {
                        await o.contentAwareFill()
                    }
                    async createLayerMask(a, e) {
                        await o.createLayerMask(u(a[0]))
                    }
                    async createLayerMaskFromSelection(a, e) {
                        await o.createLayerMaskFromSelection()
                    }
                    async toggleLayerMaskSelection(a, e) {
                        await o.toggleLayerMaskSelection()
                    }
                    async layerDeleteUserMask(a, e) {
                        await o.deleteUserMask()
                    }
                    async layerDeleteVectorMask(a, e) {
                        await o.deleteVectorMask()
                    }
                    async layerVisibleToggle(a, e) {
                        await o.layerVisibleToggle()
                    }
                    async clippingMaskToggle(a, e) {
                        await o.clippingMaskToggle()
                    }
                    async groupLayers(a, e) {
                        await o.groupLayers()
                    }
                    async smartObjectToggle(a, e) {
                        await o.smartObjectToggle(),
                        await this._sendLayerInfo()
                    }
                    async mergeVisible(a, e) {
                        await o.mergeVisible()
                    }
                    async toggleSelectedLayersLink(a, e) {
                        await o.toggleSelectedLayersLink()
                    }
                    async unlinkSelectedLayers(a, e) {
                        await o.unlinkSelectedLayers()
                    }
                    async selectLinkedLayers(a, e) {
                        await o.selectLinkedLayers()
                    }
                    async copyLayerStyle(a, e) {
                        await o.copyLayerStyle()
                    }
                    async pasteLayerStyle(a, e) {
                        await o.pasteLayerStyle()
                    }
                    async clearLayerStyle(a, e) {
                        await o.clearLayerStyle()
                    }
                    async transformOffset(a, e) {
                        await o.transformOffset(e[0], e[1]),
                        await r.wait(20)
                    }
                    async transformProportions(a, e) {
                        await o.transformProportions(e[0], e[1]),
                        await r.wait(20)
                    }
                    async transformRotate(a, e) {
                        await o.transformRotate(e[0]),
                        await r.wait(60)
                    }
                    async transformFlip(a, e) {
                        await o.transformFlip(a[0])
                    }
                    async vectorMaskDensity(a, e) {
                        await o.vectorMaskDensity(e[0])
                    }
                    async vectorMaskFeather(a, e) {
                        await o.vectorMaskFeather(e[0])
                    }
                    async userMaskDensity(a, e) {
                        await o.userMaskDensity(e[0])
                    }
                    async userMaskFeather(a, e) {
                        await o.userMaskFeather(e[0])
                    }
                    async setLayerBlendMode(a, e) {
                        await o.setBlendModeLoop(e[0])
                    }
                    async setLayerBlendModeNormal(a, e) {
                        await o.setBlendMode("normal")
                    }
                    async setLayerBlendModeDissolve(a, e) {
                        await o.setBlendMode("dissolve")
                    }
                    async setLayerBlendModeDarken(a, e) {
                        await o.setBlendMode("darken")
                    }
                    async setLayerBlendModeMultiply(a, e) {
                        await o.setBlendMode("multiply")
                    }
                    async setLayerBlendModeColorBurn(a, e) {
                        await o.setBlendMode("colorBurn")
                    }
                    async setLayerBlendModeLinearBurn(a, e) {
                        await o.setBlendMode("linearBurn")
                    }
                    async setLayerBlendModeDarkerColor(a, e) {
                        await o.setBlendMode("darkerColor")
                    }
                    async setLayerBlendModeLighten(a, e) {
                        await o.setBlendMode("lighten")
                    }
                    async setLayerBlendModeScreen(a, e) {
                        await o.setBlendMode("screen")
                    }
                    async setLayerBlendModeColorDodge(a, e) {
                        await o.setBlendMode("colorDodge")
                    }
                    async setLayerBlendModeLinearDodge(a, e) {
                        await o.setBlendMode("linearDodge")
                    }
                    async setLayerBlendModeLighterColor(a, e) {
                        await o.setBlendMode("lighterColor")
                    }
                    async setLayerBlendModeOverlay(a, e) {
                        await o.setBlendMode("overlay")
                    }
                    async setLayerBlendModeSoftLight(a, e) {
                        await o.setBlendMode("softLight")
                    }
                    async setLayerBlendModeHardLight(a, e) {
                        await o.setBlendMode("hardLight")
                    }
                    async setLayerBlendModeVividLight(a, e) {
                        await o.setBlendMode("vividLight")
                    }
                    async setLayerBlendModeLinearLight(a, e) {
                        await o.setBlendMode("linearLight")
                    }
                    async setLayerBlendModePinLight(a, e) {
                        await o.setBlendMode("pinLight")
                    }
                    async setLayerBlendModeHardMix(a, e) {
                        await o.setBlendMode("hardMix")
                    }
                    async setLayerBlendModeDifference(a, e) {
                        await o.setBlendMode("difference")
                    }
                    async setLayerBlendModeExclusion(a, e) {
                        await o.setBlendMode("exclusion")
                    }
                    async setLayerBlendModeBlendSubtraction(a, e) {
                        await o.setBlendMode("blendSubtraction")
                    }
                    async setLayerBlendModeBlendDivide(a, e) {
                        await o.setBlendMode("blendDivide")
                    }
                    async setLayerBlendModeHue(a, e) {
                        await o.setBlendMode("hue")
                    }
                    async setLayerBlendModeSaturation(a, e) {
                        await o.setBlendMode("saturation")
                    }
                    async setLayerBlendModeColor(a, e) {
                        await o.setBlendMode("color")
                    }
                    async setLayerBlendModeLuminosity(a, e) {
                        await o.setBlendMode("luminosity")
                    }
                    async executePSAction(a, e) {
                        await s.executePSAction(a[0])
                    }
                    async setTool(a, e) {
                        await s.setTool(a[0])
                    }
                    async setPrevTool(a, e) {
                        await s.setPrevTool()
                    }
                    async activateFreeTransform(a, e) {
                        await s.activateFreeTransform()
                    }
                    async applyStroke(a, e) {
                        await s.applyStroke()
                    }
                    async rotateCanvas(a, e) {
                        await s.rotateCanvas(e[0]),
                        await r.wait(50)
                    }
                    async setHistoryState(a, e) {
                        await s.setHistoryState(e[0]),
                        await r.wait(15)
                    }
                    async adjustmentLayerAutoBrightnessAndContrast(a, e) {
                        await c.autoBrightnessAndContrast(!1)
                    }
                    async adjustmentLayerLegacyAutoBrightnessAndContrast(a, e) {
                        await c.autoBrightnessAndContrast(!0)
                    }
                    async adjustmentLayerAdjust(a, e) {
                        await c.adjust(e[0], a[0]),
                        await r.wait(20)
                    }
                    async createAdjustmentLayer(a, e) {
                        await c.create(a[0]),
                        await this._sendLayerInfo()
                    }
                    async adjustmentLayerExposure(a, e) {
                        await c.adjustExposure(e[0], "exposure", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerExposureOffset(a, e) {
                        await c.adjustExposure(e[0], "offset", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerExposureGamma(a, e) {
                        await c.adjustExposure(e[0], "gamma", 1),
                        await r.wait(20)
                    }
                    async adjustmentLayerBrightness(a, e) {
                        await c.adjustBrightness(e[0], "brightness", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerBrightnessContrast(a, e) {
                        await c.adjustBrightness(e[0], "contrast", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerLevelsInBlack(a, e) {
                        await c.adjustLevels(e[0], "inBlack", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerLevelsInWhite(a, e) {
                        await c.adjustLevels(e[0], "inWhite", 255),
                        await r.wait(20)
                    }
                    async adjustmentLayerLevelsOutBlack(a, e) {
                        await c.adjustLevels(e[0], "outBlack", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerLevelsOutWhite(a, e) {
                        await c.adjustLevels(e[0], "outWhite", 255),
                        await r.wait(20)
                    }
                    async adjustmentLayerLevelsGamma(a, e) {
                        await c.adjustLevels(e[0], "gamma", 1),
                        await r.wait(20)
                    }
                    async adjustmentLayerVibrance(a, e) {
                        await c.adjustVibrance(e[0], "vibrance", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerVibranceSaturation(a, e) {
                        await c.adjustVibrance(e[0], "saturation", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerHueSaturationHue(a, e) {
                        await c.adjustHueSaturationHue(e[0], Number(a[0])),
                        await r.wait(20)
                    }
                    async adjustmentLayerHueSaturationSat(a, e) {
                        await c.adjustHueSaturationSaturation(e[0], Number(a[0])),
                        await r.wait(20)
                    }
                    async adjustmentLayerHueSaturationLightness(a, e) {
                        await c.adjustHueSaturationLightness(e[0], Number(a[0])),
                        await r.wait(20)
                    }
                    async adjustmentLayerHueSaturationBeginRamp(a, e) {
                        await c.adjustHueSaturationBeginRamp(e[0], Number(a[0])),
                        await r.wait(20)
                    }
                    async adjustmentLayerHueSaturationBeginSustain(a, e) {
                        await c.adjustHueSaturationBeginSustain(e[0], Number(a[0])),
                        await r.wait(20)
                    }
                    async adjustmentLayerHueSaturationEndSustain(a, e) {
                        await c.adjustHueSaturationEndSustain(e[0], Number(a[0])),
                        await r.wait(20)
                    }
                    async adjustmentLayerHueSaturationEndRamp(a, e) {
                        await c.adjustHueSaturationEndRamp(e[0], Number(a[0])),
                        await r.wait(20)
                    }
                    async adjustmentLayerToggleHueSaturationColorize(a, e) {
                        await c.toggleHueSaturationColorize()
                    }
                    async adjustmentLayerColorBalanceShadowsCyanRed(a, e) {
                        await c.adjustColorBalance(e[0], "shadows", "cyanRed", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorBalanceShadowsMagentaGreen(a, e) {
                        await c.adjustColorBalance(e[0], "shadows", "magentaGreen", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorBalanceShadowsYellowBlue(a, e) {
                        await c.adjustColorBalance(e[0], "shadows", "yellowBlue", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorBalanceMidtoneLevelsCyanRed(a, e) {
                        await c.adjustColorBalance(e[0], "midtones", "cyanRed", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorBalanceMidtoneLevelsMagentaGreen(a, e) {
                        await c.adjustColorBalance(e[0], "midtones", "magentaGreen", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorBalanceMidtoneLevelsYellowBlue(a, e) {
                        await c.adjustColorBalance(e[0], "midtones", "yellowBlue", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorBalanceHighlightLevelsCyanRed(a, e) {
                        await c.adjustColorBalance(e[0], "highlights", "cyanRed", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorBalanceHighlightLevelsMagentaGreen(a, e) {
                        await c.adjustColorBalance(e[0], "highlights", "magentaGreen", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorBalanceHighlightLevelsYellowBlue(a, e) {
                        await c.adjustColorBalance(e[0], "highlights", "yellowBlue", 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerBlackAndWhiteRed(a, e) {
                        await c.adjustBlackAndWhite(e[0], "red", 40),
                        await r.wait(20)
                    }
                    async adjustmentLayerBlackAndWhiteYellow(a, e) {
                        await c.adjustBlackAndWhite(e[0], "yellow", 60),
                        await r.wait(20)
                    }
                    async adjustmentLayerBlackAndWhiteGreen(a, e) {
                        await c.adjustBlackAndWhite(e[0], "green", 40),
                        await r.wait(20)
                    }
                    async adjustmentLayerBlackAndWhiteCyan(a, e) {
                        await c.adjustBlackAndWhite(e[0], "cyan", 60),
                        await r.wait(20)
                    }
                    async adjustmentLayerBlackAndWhiteBlue(a, e) {
                        await c.adjustBlackAndWhite(e[0], "blue", 20),
                        await r.wait(20)
                    }
                    async adjustmentLayerBlackAndWhiteMagenta(a, e) {
                        await c.adjustBlackAndWhite(e[0], "magenta", 80),
                        await r.wait(20)
                    }
                    async adjustmentLayerPhotoFilterDensity(a, e) {
                        await c.adjustPhotoFilterDensity(e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerPhotoFilterColorHue(a, e) {
                        await c.adjustPhotoFilterColor(e[0], 0, 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerPhotoFilterColorSaturation(a, e) {
                        await c.adjustPhotoFilterColor(0, e[0], 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerPhotoFilterColorBrightness(a, e) {
                        await c.adjustPhotoFilterColor(0, 0, e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerPhotoFilterTogglePreserveLuminosity(a, e) {
                        await c.togglePhotoFilterPreserveLuminosity()
                    }
                    async adjustmentLayerResetChannelMixer(a, e) {
                        await c.resetChannelMixer()
                    }
                    async adjustmentLayerColorMixerRedChannelRed(a, e) {
                        await c.adjustChannelMixer("red", "red", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerRedChannelGreen(a, e) {
                        await c.adjustChannelMixer("red", "green", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerRedChannelBlue(a, e) {
                        await c.adjustChannelMixer("red", "blue", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerRedChannelContrast(a, e) {
                        await c.adjustChannelMixer("red", "constant", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerGreenChannelRed(a, e) {
                        await c.adjustChannelMixer("green", "red", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerGreenChannelGreen(a, e) {
                        await c.adjustChannelMixer("green", "green", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerGreenChannelBlue(a, e) {
                        await c.adjustChannelMixer("green", "blue", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerGreenChannelContrast(a, e) {
                        await c.adjustChannelMixer("green", "constant", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerBlueChannelRed(a, e) {
                        await c.adjustChannelMixer("blue", "red", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerBlueChannelGreen(a, e) {
                        await c.adjustChannelMixer("blue", "green", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerBlueChannelBlue(a, e) {
                        await c.adjustChannelMixer("blue", "blue", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerColorMixerBlueChannelContrast(a, e) {
                        await c.adjustChannelMixer("blue", "constant", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerToggleMonochromaticChannelMixer(a, e) {
                        await c.toggleMonochromaticChannelMixer(),
                        await r.wait(20)
                    }
                    async adjustmentLayerPosterizeLevels(a, e) {
                        await c.adjustPosterizeLevels(e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerThresholdLevel(a, e) {
                        await c.adjustThresholdLevel(e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerToggleSelectiveColorMethod(a, e) {
                        await c.toggleSelectiveColorMethod(),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorRedsCyan(a, e) {
                        await c.adjustSelectiveColor(0, "cyan", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorRedsMagenta(a, e) {
                        await c.adjustSelectiveColor(0, "magenta", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorRedsYellow(a, e) {
                        await c.adjustSelectiveColor(0, "yellowColor", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorRedsBlack(a, e) {
                        await c.adjustSelectiveColor(0, "black", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorYellowsCyan(a, e) {
                        await c.adjustSelectiveColor(1, "cyan", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorYellowsMagenta(a, e) {
                        await c.adjustSelectiveColor(1, "magenta", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorYellowsYellow(a, e) {
                        await c.adjustSelectiveColor(1, "yellowColor", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorYellowsBlack(a, e) {
                        await c.adjustSelectiveColor(1, "black", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorGreensCyan(a, e) {
                        await c.adjustSelectiveColor(2, "cyan", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorGreensMagenta(a, e) {
                        await c.adjustSelectiveColor(2, "magenta", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorGreensYellow(a, e) {
                        await c.adjustSelectiveColor(2, "yellowColor", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorGreensBlack(a, e) {
                        await c.adjustSelectiveColor(2, "black", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorCyansCyan(a, e) {
                        await c.adjustSelectiveColor(3, "cyan", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorCyansMagenta(a, e) {
                        await c.adjustSelectiveColor(3, "magenta", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorCyansYellow(a, e) {
                        await c.adjustSelectiveColor(3, "yellowColor", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorCyansBlack(a, e) {
                        await c.adjustSelectiveColor(3, "black", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorBluesCyan(a, e) {
                        await c.adjustSelectiveColor(4, "cyan", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorBluesMagenta(a, e) {
                        await c.adjustSelectiveColor(4, "magenta", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorBluesYellow(a, e) {
                        await c.adjustSelectiveColor(4, "yellowColor", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorBluesBlack(a, e) {
                        await c.adjustSelectiveColor(4, "black", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorMagentasCyan(a, e) {
                        await c.adjustSelectiveColor(5, "cyan", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorMagentasMagenta(a, e) {
                        await c.adjustSelectiveColor(5, "magenta", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorMagentasYellow(a, e) {
                        await c.adjustSelectiveColor(5, "yellowColor", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorMagentasBlack(a, e) {
                        await c.adjustSelectiveColor(5, "black", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorWhitesCyan(a, e) {
                        await c.adjustSelectiveColor(6, "cyan", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorWhitesMagenta(a, e) {
                        await c.adjustSelectiveColor(6, "magenta", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorWhitesYellow(a, e) {
                        await c.adjustSelectiveColor(6, "yellowColor", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorWhitesBlack(a, e) {
                        await c.adjustSelectiveColor(6, "black", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorNeutralsCyan(a, e) {
                        await c.adjustSelectiveColor(7, "cyan", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorNeutralsMagenta(a, e) {
                        await c.adjustSelectiveColor(7, "magenta", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorNeutralsYellow(a, e) {
                        await c.adjustSelectiveColor(7, "yellowColor", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorNeutralsBlack(a, e) {
                        await c.adjustSelectiveColor(7, "black", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorBlacksCyan(a, e) {
                        await c.adjustSelectiveColor(8, "cyan", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorBlacksMagenta(a, e) {
                        await c.adjustSelectiveColor(8, "magenta", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorBlacksYellow(a, e) {
                        await c.adjustSelectiveColor(8, "yellowColor", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerSelectiveColorBlacksBlack(a, e) {
                        await c.adjustSelectiveColor(8, "black", e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerGradientMapSolidColorSmoothness(a, e) {
                        await c.adjustGradientMapSolidColorSmoothness(e[0]),
                        await r.wait(50)
                    }
                    async adjustmentLayerGradientMapSolidColorHue(a, e) {
                        await c.adjustGradientMapSolidColor(Number(a[0]), e[0], 0, 0),
                        await r.wait(40)
                    }
                    async adjustmentLayerGradientMapSolidColorSaturation(a, e) {
                        await c.adjustGradientMapSolidColor(Number(a[0]), 0, e[0], 0),
                        await r.wait(40)
                    }
                    async adjustmentLayerGradientMapSolidColorBrightness(a, e) {
                        await c.adjustGradientMapSolidColor(Number(a[0]), 0, 0, e[0]),
                        await r.wait(40)
                    }
                    async adjustmentLayerGradientMapSolidColorLocation(a, e) {
                        await c.adjustGradientMapSolidColorLocation(Number(a[0]), e[0]),
                        await r.wait(40)
                    }
                    async adjustmentLayerGradientMapSolidColorMidpoint(a, e) {
                        await c.adjustGradientMapSolidColorMidpoint(Number(a[0]), e[0]),
                        await r.wait(40)
                    }
                    async adjustmentLayerGradientMapTransparencyOpacity(a, e) {
                        await c.adjustGradientMapTransparencyOpacity(Number(a[0]), e[0]),
                        await r.wait(40)
                    }
                    async adjustmentLayerGradientMapTransparencyLocation(a, e) {
                        await c.adjustGradientMapTransparencyLocation(Number(a[0]), e[0]),
                        await r.wait(40)
                    }
                    async adjustmentLayerGradientMapTransparencyMidpoint(a, e) {
                        await c.adjustGradientMapTransparencyMidpoint(Number(a[0]), e[0]),
                        await r.wait(40)
                    }
                    async adjustmentLayerGradientMapNoiseRoughness(a, e) {
                        await c.adjustGradientMapNoiseRoughness(e[0]),
                        await r.wait(40)
                    }
                    async adjustmentLayerGradientMapNoiseMaximumHue(a, e) {
                        await c.adjustGradientMapNoiseMaximum(e[0], 0, 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerGradientMapNoiseMaximumSaturation(a, e) {
                        await c.adjustGradientMapNoiseMaximum(0, e[0], 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerGradientMapNoiseMaximumBrightness(a, e) {
                        await c.adjustGradientMapNoiseMaximum(0, 0, e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerGradientMapNoiseMinimumHue(a, e) {
                        await c.adjustGradientMapNoiseMinimum(e[0], 0, 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerGradientMapNoiseMinimumSaturation(a, e) {
                        await c.adjustGradientMapNoiseMinimum(0, e[0], 0),
                        await r.wait(20)
                    }
                    async adjustmentLayerGradientMapNoiseMinimumBrightness(a, e) {
                        await c.adjustGradientMapNoiseMinimum(0, 0, e[0]),
                        await r.wait(20)
                    }
                    async adjustmentLayerGradientMapNextNoiseColorSpace(a, e) {
                        await c.nextGradientMapNoiseColorSpace()
                    }
                    async adjustmentLayerGradientMapDither(a, e) {
                        await c.toggleGradientMapDither()
                    }
                    async adjustmentLayerGradientMapReverse(a, e) {
                        await c.toggleGradientMapReverse()
                    }
                    async adjustmentLayerGradientMapType(a, e) {
                        await c.toggleGradientMapType(),
                        await this._sendLayerInfo()
                    }
                    async adjustmentLayerGradientMapSolidColorAdd(a, e) {
                        await c.gradientMapSolidColorAdd(),
                        await this._sendLayerInfo()
                    }
                    async adjustmentLayerGradientMapTransparencyAdd(a, e) {
                        await c.gradientMapTransparencyAdd(),
                        await this._sendLayerInfo()
                    }
                    async adjustmentLayerGradientMapSolidColorDelete(a, e) {
                        await c.gradientMapSolidColorDelete(Number(a[0])),
                        await this._sendLayerInfo()
                    }
                    async adjustmentLayerGradientMapTransparencyDelete(a, e) {
                        await c.gradientMapTransparencyDelete(Number(a[0])),
                        await this._sendLayerInfo()
                    }
                    async adjustmentLayerGradientMapNoiseRestrictColors(a, e) {
                        await c.toggleGradientMapNoiseRestrictColors()
                    }
                    async adjustmentLayerGradientMapTypeNoiseShowTransparency(a, e) {
                        await c.toggleGradientMapNoiseShowTransparency()
                    }
                    async adjustmentLayerGradientMapNoiseRandomize(a, e) {
                        await c.gradientMapNoiseRandomize()
                    }
                    async adjustmentLayerCurvesInput(a, e) {
                        await c.adjustCurves(Number(a[0]), Number(a[1]), e[0], 0),
                        await r.wait(10)
                    }
                    async adjustmentLayerCurvesOutput(a, e) {
                        await c.adjustCurves(Number(a[0]), Number(a[1]), 0, e[0]),
                        await r.wait(10)
                    }
                    async adjustmentLayerCurvesAdd(a, e) {
                        await c.addCurve(Number(a[0])),
                        await this._sendLayerInfo()
                    }
                    async adjustmentLayerCurvesReset(a, e) {
                        await c.resetCurveAdjustment(Number(a[0])),
                        await this._sendLayerInfo()
                    }
                    async adjustmentLayerCurvesDelete(a, e) {
                        await c.deleteCurve(Number(a[0]), Number(a[1])),
                        await this._sendLayerInfo()
                    }
                    async adjustmentLayerToggleColorBalancePreserveLuminosity(a, e) {
                        await c.toggleColorBalancePreserveLuminosity()
                    }
                    async imageAdjustmentInvert(a, e) {
                        await n.performMenuCommand({
                            commandID: 1701
                        })
                    }
                    async imageAdjustmentDesaturate(a, e) {
                        await n.performMenuCommand({
                            commandID: 1809
                        })
                    }
                    async imageAdjustmentEqualize(a, e) {
                        await n.performMenuCommand({
                            commandID: 1702
                        })
                    }
                    async openBrightnessContrastDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1803
                        })
                    }
                    async openLevelsDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1801
                        })
                    }
                    async openCurvesDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1802
                        })
                    }
                    async openExposureDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 3067
                        })
                    }
                    async openVibranceDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1827
                        })
                    }
                    async openHueSaturationDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1805
                        })
                    }
                    async openColorBalanceDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1804
                        })
                    }
                    async openBlackAndWhiteDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1824
                        })
                    }
                    async openPhotoFilterDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 3063
                        })
                    }
                    async openChannelMixerDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 3056
                        })
                    }
                    async openColorLookupDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 3066
                        })
                    }
                    async openPosterizeDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1704
                        })
                    }
                    async openThresholdDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1703
                        })
                    }
                    async openGradientMapDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 3062
                        })
                    }
                    async openSelectiveColorDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1807
                        })
                    }
                    async openShadowHighlightsDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 3065
                        })
                    }
                    async openMatchColorDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1822
                        })
                    }
                    async openReplaceColorDialog(a, e) {
                        await n.performMenuCommand({
                            commandID: 1806
                        })
                    }
                    async adjustImageBrightness(a, e) {
                        await imageAdjustmentsInstance.brightness(e[0]),
                        await r.wait(50)
                    }
                    async adjustImageContrast(a, e) {
                        await imageAdjustmentsInstance.contrast(e[0]),
                        await r.wait(50)
                    }
                    async adjustImageLevelsInput(a, e) {
                        await imageAdjustmentsInstance.levels(e[0], 0, 0),
                        await r.wait(60)
                    }
                    async adjustImageLevelsOutput(a, e) {
                        await imageAdjustmentsInstance.levels(0, e[0], 0),
                        await r.wait(60)
                    }
                    async adjustImageLevelsGamma(a, e) {
                        await imageAdjustmentsInstance.levels(0, 0, e[0]),
                        await r.wait(60)
                    }
                    async adjustImageExposureValue(a, e) {
                        await imageAdjustmentsInstance.exposure("exposure", e[0] / 50),
                        await r.wait(60)
                    }
                    async adjustImageExposureOffset(a, e) {
                        await imageAdjustmentsInstance.exposure("offset", e[0] / 500),
                        await r.wait(60)
                    }
                    async adjustImageExposureGammaCorrection(a, e) {
                        await imageAdjustmentsInstance.exposure("gamma", e[0] > 0 ? 1.1 : .9),
                        await r.wait(60)
                    }
                    async adjustImageVibranceValue(a, e) {
                        await imageAdjustmentsInstance.vibrance("vibrance", e[0]),
                        await r.wait(50)
                    }
                    async adjustImageVibranceSaturation(a, e) {
                        await imageAdjustmentsInstance.vibrance("saturation", e[0]),
                        await r.wait(50)
                    }
                    async adjustImageHueSaturationHue(a, e) {
                        await imageAdjustmentsInstance.hueSaturation(e[0], 0, 0),
                        await r.wait(50)
                    }
                    async adjustImageHueSaturationLightness(a, e) {
                        await imageAdjustmentsInstance.hueSaturation(0, e[0], 0),
                        await r.wait(50)
                    }
                    async adjustImageHueSaturationSaturation(a, e) {
                        await imageAdjustmentsInstance.hueSaturation(0, 0, e[0]),
                        await r.wait(50)
                    }
                    async adjustImageColorBalanceHighlightCyanRed(a, e) {
                        await imageAdjustmentsInstance.colorBalance("highlightLevels", e[0], 0, 0),
                        await r.wait(50)
                    }
                    async adjustImageColorBalanceHighlightMagentaGreen(a, e) {
                        await imageAdjustmentsInstance.colorBalance("highlightLevels", 0, e[0], 0),
                        await r.wait(50)
                    }
                    async adjustImageColorBalanceHighlightYellowBlue(a, e) {
                        await imageAdjustmentsInstance.colorBalance("highlightLevels", 0, 0, e[0]),
                        await r.wait(50)
                    }
                    async adjustImageColorBalanceMidtoneLevelsCyanRed(a, e) {
                        await imageAdjustmentsInstance.colorBalance("midtoneLevels", e[0], 0, 0),
                        await r.wait(50)
                    }
                    async adjustImageColorBalanceMidtoneLevelsMagentaGreen(a, e) {
                        await imageAdjustmentsInstance.colorBalance("midtoneLevels", 0, e[0], 0),
                        await r.wait(50)
                    }
                    async adjustImageColorBalanceMidtoneLevelsYellowBlue(a, e) {
                        await imageAdjustmentsInstance.colorBalance("midtoneLevels", 0, 0, e[0]),
                        await r.wait(50)
                    }
                    async adjustImageColorBalanceShadowLevelsCyanRed(a, e) {
                        await imageAdjustmentsInstance.colorBalance("shadowLevels", e[0], 0, 0),
                        await r.wait(50)
                    }
                    async adjustImageColorBalanceShadowLevelsMagentaGreen(a, e) {
                        await imageAdjustmentsInstance.colorBalance("shadowLevels", 0, e[0], 0),
                        await r.wait(50)
                    }
                    async adjustImageColorBalanceShadowLevelsYellowBlue(a, e) {
                        await imageAdjustmentsInstance.colorBalance("shadowLevels", 0, 0, e[0]),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerRedChannelRed(a, e) {
                        await imageAdjustmentsInstance.channelMixer("red", e[0], 0, 0, 0),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerRedChannelGreen(a, e) {
                        await imageAdjustmentsInstance.channelMixer("red", 0, e[0], 0, 0),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerRedChannelBlue(a, e) {
                        await imageAdjustmentsInstance.channelMixer("red", 0, 0, e[0], 0),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerRedChannelContrast(a, e) {
                        await imageAdjustmentsInstance.channelMixer("red", 0, 0, 0, e[0]),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerGreenChannelRed(a, e) {
                        await imageAdjustmentsInstance.channelMixer("green", e[0], 0, 0, 0),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerGreenChannelGreen(a, e) {
                        await imageAdjustmentsInstance.channelMixer("green", 0, e[0], 0, 0),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerGreenChannelBlue(a, e) {
                        await imageAdjustmentsInstance.channelMixer("green", 0, 0, e[0], 0),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerGreenChannelContrast(a, e) {
                        await imageAdjustmentsInstance.channelMixer("green", 0, 0, 0, e[0]),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerBlueChannelRed(a, e) {
                        await imageAdjustmentsInstance.channelMixer("blue", e[0], 0, 0, 0),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerBlueChannelGreen(a, e) {
                        await imageAdjustmentsInstance.channelMixer("blue", 0, e[0], 0, 0),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerBlueChannelBlue(a, e) {
                        await imageAdjustmentsInstance.channelMixer("blue", 0, 0, e[0], 0),
                        await r.wait(50)
                    }
                    async adjustImageColorMixerBlueChannelContrast(a, e) {
                        await imageAdjustmentsInstance.channelMixer("blue", 0, 0, 0, e[0]),
                        await r.wait(50)
                    }
                    async adjustImageShadows(a, e) {
                        await imageAdjustmentsInstance.shadowsHighlights("shadowMode", e[0]),
                        await r.wait(50)
                    }
                    async adjustImageHighlights(a, e) {
                        await imageAdjustmentsInstance.shadowsHighlights("highlightMode", e[0]),
                        await r.wait(50)
                    }
                    async textSize(a, e) {
                        await textInstance.textSize(e[0]),
                        await r.wait(50)
                    }
                    async scrollFont(a, e) {
                        await textInstance.scrollFont(e[0]),
                        await r.wait(50)
                    }
                    async scrollFontStyle(a, e) {
                        await textInstance.scrollFontStyle(e[0]),
                        await r.wait(50)
                    }
                    async leading(a, e) {
                        await textInstance.leading(e[0]),
                        await r.wait(20)
                    }
                    async leadingAuto(a, e) {
                        await textInstance.leadingAuto()
                    }
                    async tracking(a, e) {
                        await textInstance.tracking(e[0]),
                        await r.wait(20)
                    }
                    async nextKerningType(a, e) {
                        await textInstance.nextKerningType()
                    }
                    async textColorHSB(a, e) {
                        await textInstance.textColor(e[0], e[1], e[2])
                    }
                    async textColorHue(a, e) {
                        await textInstance.textColor(e[0], 0, 0)
                    }
                    async textColorSaturation(a, e) {
                        await textInstance.textColor(0, e[0], 0)
                    }
                    async textColorBrightness(a, e) {
                        await textInstance.textColor(0, 0, e[0])
                    }
                    async vectorLayerFillColorHSB(a, e) {
                        await vectorLayerInstance.fillColor(e[0], e[1], e[2])
                    }
                    async vectorLayerFillColorHue(a, e) {
                        await vectorLayerInstance.fillColor(e[0], 0, 0)
                    }
                    async vectorLayerFillColorSaturation(a, e) {
                        await vectorLayerInstance.fillColor(0, e[0], 0)
                    }
                    async vectorLayerFillColorBrightness(a, e) {
                        await vectorLayerInstance.fillColor(0, 0, e[0])
                    }
                    async vectorLayerLineColorHSB(a, e) {
                        await vectorLayerInstance.lineColor(e[0], e[1], e[2])
                    }
                    async vectorLayerLineColorHue(a, e) {
                        await vectorLayerInstance.lineColor(e[0], 0, 0)
                    }
                    async vectorLayerLineColorSaturation(a, e) {
                        await vectorLayerInstance.lineColor(0, e[0], 0)
                    }
                    async vectorLayerLineColorBrightness(a, e) {
                        await vectorLayerInstance.lineColor(0, 0, e[0])
                    }
                    async vectorLayerLineWidth(a, e) {
                        await vectorLayerInstance.lineWidth(e[0]),
                        await r.wait(10)
                    }
                    async vectorLayerStrokeType(a, e) {
                        await vectorLayerInstance.setLineCapTypePreset(a[0])
                    }
                    async vectorLayerStrokeDash(a, e) {
                        await vectorLayerInstance.strokeDash(e[0]),
                        await r.wait(10)
                    }
                    async vectorLayerStrokeGap(a, e) {
                        await vectorLayerInstance.strokeGap(e[0]),
                        await r.wait(10)
                    }
                    async vectorLayerNextLineAlignment(a, e) {
                        await vectorLayerInstance.nextLineAlignment()
                    }
                    async vectorLayerNextLineCapType(a, e) {
                        await vectorLayerInstance.nextLineCapType()
                    }
                    async vectorLayerNextLineJoinType(a, e) {
                        await vectorLayerInstance.nextLineJoinType()
                    }
                    async vectorLayerPathCornersRadiusTopLeft(a, e) {
                        await vectorLayerInstance.pathCornersRadius(0, e[0], 0, 0),
                        await r.wait(20)
                    }
                    async vectorLayerPathCornersRadiusTopRight(a, e) {
                        await vectorLayerInstance.pathCornersRadius(e[0], 0, 0, 0),
                        await r.wait(20)
                    }
                    async vectorLayerPathCornersRadiusBottomLeft(a, e) {
                        await vectorLayerInstance.pathCornersRadius(0, 0, e[0], 0),
                        await r.wait(20)
                    }
                    async vectorLayerPathCornersRadiusBottomRight(a, e) {
                        await vectorLayerInstance.pathCornersRadius(0, 0, 0, e[0]),
                        await r.wait(20)
                    }
                    async vectorLayerPathAllCornersRadius(a, e) {
                        const t = e[0];
                        await vectorLayerInstance.pathCornersRadius(t, t, t, t),
                        await r.wait(20)
                    }
                    async vectorLayerNextPathActionMode(a, e) {
                        await vectorLayerInstance.nextPathActionMode()
                    }
                    async vectorLayerToggleStroke(a, e) {
                        await vectorLayerInstance.toggleStroke()
                    }
                    async artboardLayerWidth(a, e) {
                        await artboardLayerInstance.proportions(e[0], 0),
                        await r.wait(30)
                    }
                    async artboardLayerHeight(a, e) {
                        await artboardLayerInstance.proportions(0, e[0]),
                        await r.wait(30)
                    }
                    async artboardLayerScale(a, e) {
                        await artboardLayerInstance.proportions(e[0], e[0]),
                        await r.wait(30)
                    }
                    async artboardLayerOffsetX(a, e) {
                        await artboardLayerInstance.offset(e[0], 0),
                        await r.wait(30)
                    }
                    async artboardLayerOffsetY(a, e) {
                        await artboardLayerInstance.offset(0, e[0]),
                        await r.wait(30)
                    }
                    async artboardLayerNextBackgroundType(a, e) {
                        await artboardLayerInstance.nextBackgroundType()
                    }
                    async artboardLayerColor(a, e) {
                        await artboardLayerInstance.color(e[0], e[1], e[2])
                    }
                    async artboardLayerColorHue(a, e) {
                        await artboardLayerInstance.color(e[0], 0, 0)
                    }
                    async artboardLayerColorSaturation(a, e) {
                        await artboardLayerInstance.color(0, e[0], 0)
                    }
                    async artboardLayerColorBrightness(a, e) {
                        await artboardLayerInstance.color(0, 0, e[0])
                    }
                    async frameLayerLineWidth(a, e) {
                        await frameLayerInstance.lineWidth(e[0])
                    }
                    async frameLayerLineColorHue(a, e) {
                        await frameLayerInstance.lineColor(e[0], 0, 0)
                    }
                    async frameLayerLineColorSaturation(a, e) {
                        await frameLayerInstance.lineColor(0, e[0], 0)
                    }
                    async frameLayerLineColorBrightness(a, e) {
                        await frameLayerInstance.lineColor(0, 0, e[0])
                    }
                    async frameLayerNextLineAlignment(a, e) {
                        await frameLayerInstance.nextLineAlignment()
                    }
                    async frameLayerToggleStroke(a, e) {
                        await frameLayerInstance.toggleStroke()
                    }
                    async frameLayerWidth(a, e) {
                        await frameLayerInstance.proportions(e[0], 0),
                        await r.wait(20)
                    }
                    async frameLayerHeight(a, e) {
                        await frameLayerInstance.proportions(0, e[0]),
                        await r.wait(20)
                    }
                    async frameLayerScale(a, e) {
                        await frameLayerInstance.proportions(e[0], e[0]),
                        await r.wait(20)
                    }
                    async frameLayerOffsetX(a, e) {
                        await frameLayerInstance.offset(e[0], 0),
                        await r.wait(20)
                    }
                    async frameLayerOffsetY(a, e) {
                        await frameLayerInstance.offset(0, e[0]),
                        await r.wait(20)
                    }
                    async _sendLayerInfo() {
                        const a = await o.getLayerInfo();
                        this._communicationService.send({
                            type: "getLayerInfoResponse",
                            payload: JSON.stringify(a)
                        })
                    }
                }
            }
            ,
            116: (a,e,t)=>{
                const n = t(770)
                  , r = t(192).core;
                class i {
                    constructor() {}
                    static Instance() {
                        return this._instance || (this._instance = new i),
                        this._instance
                    }
                    async zoom(a) {
                        a = n.maxMin(a, 15, -15);
                        const e = await this._getCurrentZoomVal()
                          , t = .03 * e
                          , r = n.maxMin(e + t * a, 4e3, 0);
                        r && await n.executeBatchPlay({
                            _obj: "set",
                            _target: {
                                _ref: [{
                                    _property: "zoom"
                                }, {
                                    _ref: "document",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            },
                            to: {
                                _obj: "zoom",
                                zoom: {
                                    _unit: "percentUnit",
                                    _value: r
                                }
                            },
                            _options: {
                                dialogOptions: "silent"
                            }
                        })
                    }
                    async zoomToFit() {
                        await r.performMenuCommand({
                            commandID: 1192
                        })
                    }
                    async _getCurrentZoomVal() {
                        return (await n.executeBatchPlay({
                            _obj: "get",
                            _target: {
                                _ref: [{
                                    _property: "zoom"
                                }, {
                                    _ref: "document",
                                    _enum: "ordinal",
                                    _value: "targetEnum"
                                }]
                            }
                        }))[0].zoom._value
                    }
                }
                e.q = i.Instance()
            }
            ,
            770: (a,e,t)=>{
                e.getApplicationDescriptor = async function() {
                    return (await t(192).action.batchPlay([{
                        _obj: "get",
                        _target: {
                            _ref: "application",
                            _enum: "ordinal",
                            _value: "targetEnum"
                        }
                    }], {}))[0]
                }
                ,
                e.executeBatchPlay = async function(a) {
                    const e = await t(192).action.batchPlay([a], {
                        synchronousExecution: !1,
                        dialogOptions: "silent",
                        commandEnablement: "never"
                    });
                    if (e[0].message)
                        throw e[0].message;
                    return e
                }
                ,
                e.maxMin = function(a, e, t) {
                    return Math.max(Math.min(a, e), t)
                }
                ,
                e.wait = async function(a) {
                    return new Promise((e=>setTimeout(e, a)))
                }
                ,
                e.checkPSPlugin = function() {
                    const a = t(876).entrypoints._pluginInfo.manifest.name
                      , e = t(876).host.name;
                    return "TourBox" === a && "Photoshop" === e
                }
            }
            ,
            311: (a,e,t)=>{
                const n = t(770);
                a.exports = class {
                    constructor(a, e) {
                        this._commandsQueue = [],
                        this._communicationService = a,
                        this._commandsHandler = e,
                        this._backgroundWorker()
                    }
                    HandleCommand(a) {
                        const e = this._commandsQueue.findIndex((e=>e.tn === a.tn));
                        if (e < 0)
                            this._commandsQueue.push(a);
                        else {
                            if (!a.incs)
                                return;
                            a.incs.forEach(((a,t)=>{
                                this._commandsQueue[e].incs[t] += a
                            }
                            ))
                        }
                    }
                    async _backgroundWorker() {
                        for (; ; )
                            try {
                                if (this._commandsQueue.length > 0) {
                                    let a;
                                    try {
                                        a = this._commandsQueue.shift(),
                                        await this._commandsHandler.handleCommand(a),
                                        await n.wait(10)
                                    } catch (e) {
                                        this._onError(a, e),
                                        await n.wait(100)
                                    }
                                } else
                                    await n.wait(10)
                            } catch (a) {
                                this._onError(null, a),
                                await n.wait(100)
                            }
                    }
                    _onError(a, e) {
                        try {
                            const t = {
                                message: e.message,
                                command: JSON.stringify(a)
                            };
                            this._communicationService.send({
                                type: "exception",
                                payload: JSON.stringify(t)
                            })
                        } catch {}
                    }
                }
            }
            ,
            997: (a,e,t)=>{
                var n = t(598);
                const r = "onConnected"
                  , i = "onError"
                  , s = "onDisconnected"
                  , o = "onMessage";
                a.exports = class {
                    constructor() {
                        this._publisher = new n
                    }
                    connect(a) {
                        this._ws = new WebSocket("ws://localhost:" + a,"test-protocol"),
                        this._ws.addEventListener("open", (a=>{
                            this._connected = !0,
                            this._publisher.publish(r, a)
                        }
                        )),
                        this._ws.addEventListener("error", (a=>{
                            this._publisher.publish(i, a)
                        }
                        )),
                        this._ws.addEventListener("close", (a=>{
                            this._connected && this._publisher.publish(s, a),
                            this._connected = !1
                        }
                        )),
                        this._ws.addEventListener("message", (a=>{
                            this._publisher.publish(o, a.data)
                        }
                        ))
                    }
                    send(a) {
                        this._ws.send(JSON.stringify(a))
                    }
                    onConnectedSubscribe(a) {
                        this._publisher.subscribe(r, a)
                    }
                    onErrorSubscribe(a) {
                        this._publisher.subscribe(i, a)
                    }
                    onDisconnectedSubscribe(a) {
                        this._publisher.subscribe(s, a)
                    }
                    onMessagedSubscribe(a) {
                        this._publisher.subscribe(o, a)
                    }
                }
            }
            ,
            129: (a,e,t)=>{
                const n = t(271).b;
                a.exports = class {
                    constructor(a) {
                        this._communicationService = a
                    }
                    async subscribeToEvents() {
                        await this._subscribeToPhotoshopEvents()
                    }
                    async _subscribeToPhotoshopEvents() {
                        n.activeLayerChangedSubscribe((a=>{
                            this._communicationService.send({
                                type: "activeLayerChanged",
                                payload: JSON.stringify(a)
                            })
                        }
                        ))
                    }
                }
            }
            ,
            865: (a,e,t)=>{
                a.exports = class {
                    constructor() {
                        this._interval = 1e3,
                        this._portFileName = "tourbox_uxp.port",
                        this._localFileSystem = t(876).storage.localFileSystem,
                        this._continue = !1
                    }
                    async waitForPort() {
                        const a = a=>new Promise((e=>setTimeout(e, a)))
                          , e = await this._localFileSystem.getDataFolder();
                        for (this._continue = !0; this._continue; ) {
                            try {
                                let a = await e.getEntry(this._portFileName);
                                if (a) {
                                    let e = await a.read();
                                    return this._continue = !1,
                                    e
                                }
                            } catch {}
                            await a(this._interval)
                        }
                    }
                    stop() {
                        this._continue = !1
                    }
                }
            }
            ,
            598: a=>{
                a.exports = class {
                    constructor() {
                        this.list = {}
                    }
                    subscribe(a, e) {
                        this.list[a] || (this.list[a] = []),
                        this.list[a].push(e)
                    }
                    publish(a, ...e) {
                        for (let t of this.list[a])
                            t.call(this, ...e)
                    }
                    unSubscribe(a, e) {
                        let t = this.list[a];
                        if (!t)
                            return !1;
                        e ? t.forEach(((a,n)=>{
                            a === e && t.splice(n, 1)
                        }
                        )) : t && (t.length = 0)
                    }
                }
            }
            ,
            192: a=>{
                "use strict";
                a.exports = require("photoshop")
            }
            ,
            876: a=>{
                "use strict";
                a.exports = require("uxp")
            }
        }
          , e = {};
        function t(n) {
            var r = e[n];
            if (void 0 !== r)
                return r.exports;
            var i = e[n] = {
                exports: {}
            };
            return a[n](i, i.exports, t),
            i.exports
        }
        (()=>{
            t(192).app,
            t(917);
            const a = t(770);
            var e = t(865)
              , n = t(997)
              , r = t(311)
              , i = t(129)
              , s = t(307);
            !async function() {
                const t = new n
                  , o = new i(t)
                  , l = new e;
                async function c() {
                    let a = await l.waitForPort();
                    t.connect(a)
                }
                let u;
                a.checkPSPlugin() && (u = new s(t));
                const d = new r(t,u);
                t.onErrorSubscribe((a=>c())),
                t.onConnectedSubscribe((a=>{}
                )),
                t.onDisconnectedSubscribe((a=>{
                    c()
                }
                )),
                t.onMessagedSubscribe((a=>{
                    d.HandleCommand(JSON.parse(a))
                }
                )),
                o.subscribeToEvents(),
                c()
            }()
        }
        )()
    }
    )();
}
);
