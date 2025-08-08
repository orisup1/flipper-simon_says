# Flipper Zero Simon Says

## Build and Run (Desktop Simulation)

- Requirements: gcc, make
- Build: `make`
- Run: `./flipper_zero_game`

## Build and Install on Flipper (FAP)

- Requirements: `ufbt` installed and initialized in this repo
  - Install: see `https://github.com/flipperdevices/flipperzero-ufbt`
  - Initialize (once): `ufbt init`
- Build FAP: `make fap`
- The resulting `.fap` will be in `dist/` (per ufbt), deploy/install per ufbt instructions.

## Notes

- The code uses desktop fallback paths when `DESKTOP` is defined (via the Makefile).
- On Flipper, GUI and input are handled via Furi APIs; entry point is `simonsays_main` (see `application.fam`). 