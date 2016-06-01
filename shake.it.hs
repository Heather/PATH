{-# LANGUAGE UnicodeSyntax #-}

import           Shake.It.Off

main :: IO ()
main = shake $ do
  "clean" ∫ removeDirIfExists buildPath

  pathExecutable ♯ do
    current ← getCurrentDirectory
    createDirectoryIfMissing True $ current </> buildPath
    setCurrentDirectory $ current </> buildPath
    -- TODO: make it simpler
    vc ← vcshell ["140"]
    qmake [".." </> "PATH.pro"]
    system ("\"" ++ vc ++ "\" x64 8.1 && nmake release") >>= checkExitCode

 where buildPath :: String
       buildPath = "build"

       pathExecutable :: String
       pathExecutable = buildPath </> "release" </> "PATH.exe"
