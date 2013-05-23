<CsoundSynthesizer>
<CsOptions>
-odac0 -d -B10000 -b5000
</CsOptions>
<CsInstruments>
sr	= 44100
0dbfs	= 1
nchnls	= 2
ksmps	= 2

giSinus		ftgen 1, 0, 1024, 10, 1
giWindow	ftgen 2, 0, 16384, 7, 0, 4096, 1, 4096, 0.3333, 8192, 0

giBuffer1	ftgen 10, 0, 524288, 1, "bufferI.wav", 0,0,0
giBuffer1	ftgen 11, 0, 524288, 1, "bufferI.wav", 0,0,0
gkCount		init 0

gkReadBuffer	init 10
gkWriteBuffer	init 11

instr 1

		gkCount = gkCount + 1
		if gkCount > 10 goto trigg
		goto skip

trigg:
		gkCount = 0
		event_i "i", 11, 0, 8 
skip:
		iatt = p3/10
		idec = p3/5
		isus = 0.5
		irel = 0.02

kadsr		adsr iatt, idec, isus, irel


iamp		random 0.2, 0.4

		kamp = iamp
		kcps = cpsmidinn(p4)
		ifn  = giSinus

aOsc		vco2 kamp, kcps, 2, 0.7
		
aOsc		butlp aOsc, 1200
		aOsc = aOsc *kadsr

		chnmix aOsc, "instr1"
endin






instr 10
asound		chnget "instr1"

andx		linseg 0, 524288 / sr, 1
		ifn = i(gkWriteBuffer)
		imode= 1
		tablew asound, andx, ifn, imode

		event_i "i", 10, 21, 20

		itemp	     = i(gkReadBuffer)
		gkReadBuffer = i(gkWriteBuffer)
		gkWriteBuffer= itemp
endin


instr 11
/*
		kfmd = 0.9
		kcps = 4
		kgdur = 2
		kfn  = giBuffer1
		ioverlp = 256
		iwfn = giWindow

ares		grain2 kcps, kfmd, kgdur, ioverlp, kfn, iwfn
		
*/
ares		flooper 0.3, 0.5, 0.2, 0.9, 0.2, i(gkReadBuffer)
		ares = ares*0.2
		chnmix ares, "instr11"
endin


instr 12

		kamp = 0.4
		kdens = 40
		ktrans = 0.2
		aspd linseg 0, p3, 1
		koct = 1
		kband = 0.8
		kris = 0.2
		kdur = 0.2
		kdec = 0.1
		
		iolaps = 40
		ifna = i(gkReadBuffer)
		ifnb = giWindow
		itotdur = p3

ares 		fog kamp, kdens, ktrans, aspd, koct, kband, kris, kdur, kdec, iolaps, ifna, ifnb, itotdur

		chnmix ares, "instr12"
		event_i "i", 12, 60, 60

endin
instr 100

aInstr1		chnget "instr1"
aInstr11	chnget "instr11"
aInstr12	chnget "instr12"

		aL = aInstr1 + aInstr11 + aInstr12
		aR = aInstr1 + aInstr11 + aInstr12


		kfeedback = 0.6
		kfco      = sr /4
aLrev,aRrev	reverbsc aL, aR, kfeedback, kfco

		aL = aLrev + aL
		aR = aRrev + aR
		outs aL, aR

		a0 = 0;
		chnset a0, "instr1"	
		chnset a0, "instr11"
		chnset a0, "instr12"

endin
</CsInstruments>


<CsScore>
f 0 942012 1
i 10 0 20
i 1 256 0.2

i 12 10 20
i 100 0 99999999999

;i 1 1 .		74
</CsScore>


</CsoundSynthesizer>