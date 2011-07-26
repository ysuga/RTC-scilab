//
//
// author Yuki Suga


mode(-1);
lines(0);

TOOLBOX_NAME  = "RTCscilab";
TOOLBOX_TITLE = "RTCscilab";
toolbox_dir   = get_absolute_file_path("builder.sce");

// Check Scilab's version
// =============================================================================

try
	v = getversion("scilab");
catch
	error(gettext("Scilab 5.2 or more is required."));
end

if v(2) < 2 then
	// new API in scilab 5.2
	error(gettext('Scilab 5.2 or more is required.'));  
end

// Check development_tools module avaibility
// =============================================================================

if ~with_module('development_tools') then
  error(msprintf(gettext('%s module not installed."),'development_tools'));
end

// Action
// =============================================================================

tbx_builder_macros(toolbox_dir);
tbx_builder_src(toolbox_dir);
tbx_builder_gateway(toolbox_dir);
tbx_builder_help(toolbox_dir);
tbx_build_loader(TOOLBOX_NAME, toolbox_dir);
tbx_build_cleaner(TOOLBOX_NAME, toolbox_dir);

cd(toolbox_dir);
disp("Creating XCosPallete");
///exec loader.sce
getd macros;
loadXcosLibs();
pal = xcosPal("RTCscilab");

inportPath="DataInPort.h5";
outportPath="DataOutPort.h5";
clkportPath="ClockPort.h5";

scs_m = InPortGraphics("define");
export_to_hdf5(inportPath, "scs_m");
scs_m = OutPortGraphics("define");
export_to_hdf5(outportPath, "scs_m");
scs_m = XCos_ClkGFX("define");
export_to_hdf5(clkportPath, "scs_m");

pal = xcosPalAddBlock(pal, inportPath, "inport_image.png", "inport_image.svg");
pal = xcosPalAddBlock(pal, outportPath, "outport_image.png", "outport_image.svg");
pal = xcosPalAddBlock(pal, clkportPath, "clkport_image.png", "clkport_image.svg");

///xcosPalAdd(pal);

xcosPalExport(pal, "RTCscilab.xpal");

pal = xcosPalAddBlock
//exec openhrp_demo_builder.sce
// Clean variables
// =============================================================================

clear toolbox_dir TOOLBOX_NAME TOOLBOX_TITLE;
