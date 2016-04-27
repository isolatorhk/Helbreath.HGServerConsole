// include Fake lib
#r @"packages/FAKE/tools/FakeLib.dll"
open Fake


// Properties
let buildDir = "./build"

// Targets
Target "Clean" (fun _ ->
trace "--- Cleaning build and test dirs --- "
CleanDirs [buildDir]
)

Target "CopyToDebugFolder" (fun _ ->
trace "Copying from build to debug"
!! ("./build/" + "*.*")
      |> Copy "./Debug"
)

Target "BuildApp" (fun _ ->
trace "--- Building app --- "
!! "Helbreath.HGServerConsole/*.vcxproj"
 |> MSBuild "" "Build" ["Configuration", "Debug"; "PlatformToolset", "v120"; "Platform", "x86"; "OutDir", "../build"]
 |> Log "AppBuild-Output: "
)

Target "Default" (fun _ ->
trace "--- Starting... --- "
)

// start build
"Clean" ==> "BuildApp" ==> "CopyToDebugFolder" ==> "Default"

RunTargetOrDefault "Default"
