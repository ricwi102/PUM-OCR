# PUM-OCR

Libraries ligger under `PUM-OCR/lib` och antingen dlls under x32 eller x64 får koppieras in 
efter vad som kommer att användas (jag har ännu inte lyckats skapa en länk till den filen).

**NOTE**: 32 bitars versionerna inte testade. (Dock samma kod)


# .NET core
Ska bara vara att köra, måste endast ha en Nuget:
[CoreCompat.System.Drawing](https://www.nuget.org/packages/CoreCompat.System.Drawing/1.0.0-beta006)



# Installation av libraries

För att installera libraries enligt metoden jag har använt kommer
du att behöva följande:
* [CMake](https://cmake.org/)
* [CPPAN](https://cppan.org/)

Förslagsvis läggs de till i PATH. `set PATH=(path till prog);%PATH%`

Exemplen utgår från förslag på filstruktur nedan och kommandon kan justeras.

## Leptonica
Leptonica repo: [github.com/DanBloomberg/leptonica](https://github.com/DanBloomberg/leptonica)

Följ dessa steg:
1. Klona repot
2. Kör `CPPAN` i src (leptonica master)
3. Skapa build dir, exempelvis 'mkdir build64 && cd build64'
4. Kör `cmake ../leptonca-master -G "Visual Studio 15 2017 Win64"` från build dir 
5. Projektet kan sedan öppnas och byggas
6. Gå sedan in i LeptonicaTargets.cmake och ändra översta raden från `*/build/cppan.cmake`
	   till `*/build/exports/cppan.cmake`

**NOTE**: '-G "<Generator> <Arch>" väljer generator och architektur. Lämna architektur tom för 32 bitars.
Kör `cmake -h` för mer info. 

## Tesseract
Tesseract repo: [github.com/tesseract-ocr/tesseract](https://github.com/tesseract-ocr/tesseract)

Följ dessa steg:
1. Klona repot
2. Öppna `CMakeLists.txt` och lägg till följande (innan Leptonica_DIR används)
		if("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
			set(Leptonica_DIR ${PROJECT_SOURCE_DIR}/../../lept/build64)
		else()
			set(Leptonica_DIR ${PROJECT_SOURCE_DIR}/../../lept/build32)
		endif()
3. Skapa build dir, exempelvis `mkdir build64 && cd build64`
4. Kör `cmake ../tesseract-master -G "Visual Studio 15 2017 Win64"` från build dir 
5. Projektet kan sedan öppnas. Förslagsvis körs 'Unload all projects' på "Training Tools"-mappen
6. Vissa dependencies har följt med från leptonica som inte behövs och under 
`Properties->Linker->Input->Additional Dependencies` kan pvt.cppan.demo.* tas bort för tesseract och libtesseract

Enklaste vägen härifrån är att ta bort de filer som finns under tesseract projektet och lägga till de filer som finns under `PUM-OCR/tessapi-cpp/`
	


## Förslag på filstruktur
_tess-lib\n
|--_lept\n
|  |--_build32\n
|  |--_build64\n
|  |--_leptonica_master\n
|
|--_tess\n
|  |--_build32\n
|  |--_build64\n
|  |--_tesseract_master\n






