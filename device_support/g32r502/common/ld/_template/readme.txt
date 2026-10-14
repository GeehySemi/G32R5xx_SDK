FILE:    readme.txt
TITLE:   G32R502 Eclipse LD template selection and comment alignment
VERSION: 1.0.0
DATE:    2026-08-10

G32R502 Eclipse Linker Script Templates
=======================================

Location: device_support/g32r502/common/ld/_template/

This directory holds the 16 fixed-layout Eclipse / llvm-lld masters used by the linker-script verification matrix. This refresh aligns their comment shape with G32R501 while keeping every template's capacity, VECTOR mode, RWZI mode, and section placement unchanged.

Default product masters in the parent directory
-----------------------------------------------

  g32r502xc_cbus_flash.ld             -> CF-V0-R0
  g32r502xc_itcm_ram.ld               -> IR-V1-R0
  g32r502xc_cbus_flash_noramvector.ld -> CF-NV-R0
  g32r502xc_itcm_ram_noramvector.ld   -> IR-NV-R0

Template matrix
---------------

cbus_flash/
  g32r502xc_cbus_flash_vec_dtcm_rwzi_dtcm.ld    -> CF-V0-R0
  g32r502xc_cbus_flash_vec_dtcm_rwzi_itcm.ld    -> CF-V0-R1
  g32r502xc_cbus_flash_vec_dtcm_rwzi_spill.ld   -> CF-V0-R2
  g32r502xc_cbus_flash_vec_itcm_rwzi_dtcm.ld    -> CF-V1-R0
  g32r502xc_cbus_flash_vec_itcm_rwzi_itcm.ld    -> CF-V1-R1
  g32r502xc_cbus_flash_vec_itcm_rwzi_spill.ld   -> CF-V1-R2
  g32r502xc_cbus_flash_vec_none_rwzi_dtcm.ld    -> CF-V2-R0
  g32r502xc_cbus_flash_vec_none_rwzi_itcm.ld    -> CF-V2-R1
  g32r502xc_cbus_flash_vec_none_rwzi_spill.ld   -> CF-V2-R2

itcm_ram/
  g32r502xc_itcm_ram_vec_dtcm_rwzi_dtcm.ld      -> IR-V0-R0
  g32r502xc_itcm_ram_vec_itcm_rwzi_dtcm.ld      -> IR-V1-R0
  g32r502xc_itcm_ram_vec_none_rwzi_dtcm.ld      -> IR-V2-R0

cbus_flash_noramvector/
  g32r502xc_cbus_flash_noramvector_rwzi_dtcm.ld  -> CF-NV-R0
  g32r502xc_cbus_flash_noramvector_rwzi_itcm.ld  -> CF-NV-R1
  g32r502xc_cbus_flash_noramvector_rwzi_spill.ld -> CF-NV-R2

itcm_ram_noramvector/
  g32r502xc_itcm_ram_noramvector_rwzi_dtcm.ld    -> IR-NV-R0

Verification policy for this batch
----------------------------------

- All 16 template LD files receive the same comment / banner / version refresh.
- Static gate checks all 16 files for version and semantic-equivalence.
- Board-level sampling covers at least 30% of the template set (5 / 16), with at least one case from each subdirectory.

Use in a project
----------------

1. Copy one chosen .ld file from _template/<family>/ into project/Eclipse/
2. Point the Eclipse linker script setting to that file
3. Keep stack / heap / boot snapshot edits in the project copy, not here
