{-# LANGUAGE UnicodeSyntax #-}

import Shake.It.Off

main :: IO ()
main = shake $ do
  "clean" ∫ removeDirIfExists buildPath

  pathExecutable ♯ do
    current ← getCurrentDirectory
    createDirectoryIfMissing True $ current </> buildPath
    setCurrentDirectory $ current </> buildPath
    qmake [".." </> "PATH.pro"]
    make ["release"]

 where buildPath :: String
       buildPath = "build"

       pathExecutable :: String
       pathExecutable = buildPath </> "release" </> "PATH.exe"
