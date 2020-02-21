del *.asm
del *.lst
del *.rel
del *.sym
del *.ihx
del *.lk
del *.map
del *.noi

call "D:\amennelet\GameBoy\gbdk-n\bin\gbdk-n-compile.bat" main.c
call "D:\amennelet\GameBoy\gbdk-n\bin\gbdk-n-compile.bat" spritehelper.c
call "D:\amennelet\GameBoy\gbdk-n\bin\gbdk-n-compile.bat" Asset\BackgroundTiles.c
call "D:\amennelet\GameBoy\gbdk-n\bin\gbdk-n-compile.bat" Asset\SpriteTiles.c
call "D:\amennelet\GameBoy\gbdk-n\bin\gbdk-n-compile.bat" asset\KenbakBackgroundMap.c
call "D:\amennelet\GameBoy\gbdk-n\bin\gbdk-n-compile.bat" asset\KenbakMenuMap.c
call "D:\amennelet\GameBoy\gbdk-n\bin\gbdk-n-compile.bat" kenbakmachine.c
call "D:\amennelet\GameBoy\gbdk-n\bin\gbdk-n-compile.bat" kenbakscreen.c
call "D:\amennelet\GameBoy\gbdk-n\bin\gbdk-n-link.bat" main.rel spritehelper.rel BackgroundTiles.rel SpriteTiles.rel KenbakBackgroundMap.rel KenbakMenuMap.rel kenbakmachine.rel kenbakscreen.rel -o Kenbak.ihx
call "D:\amennelet\GameBoy\gbdk-n\bin\gbdk-n-make-rom.bat" Kenbak.ihx Kenbak.gb