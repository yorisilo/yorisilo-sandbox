module Paths_haskell_lambda (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
catchIO = Exception.catch

version :: Version
version = Version [0,1,0,0] []
bindir, libdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "/Users/yorisilo/Dropbox/programming/OCaml/lambda_calculus/haskell-lambda/.stack-work/install/x86_64-osx/lts-6.14/7.10.3/bin"
libdir     = "/Users/yorisilo/Dropbox/programming/OCaml/lambda_calculus/haskell-lambda/.stack-work/install/x86_64-osx/lts-6.14/7.10.3/lib/x86_64-osx-ghc-7.10.3/haskell-lambda-0.1.0.0-G7i2KeaeM0FLQ16tvTjcKH"
datadir    = "/Users/yorisilo/Dropbox/programming/OCaml/lambda_calculus/haskell-lambda/.stack-work/install/x86_64-osx/lts-6.14/7.10.3/share/x86_64-osx-ghc-7.10.3/haskell-lambda-0.1.0.0"
libexecdir = "/Users/yorisilo/Dropbox/programming/OCaml/lambda_calculus/haskell-lambda/.stack-work/install/x86_64-osx/lts-6.14/7.10.3/libexec"
sysconfdir = "/Users/yorisilo/Dropbox/programming/OCaml/lambda_calculus/haskell-lambda/.stack-work/install/x86_64-osx/lts-6.14/7.10.3/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "haskell_lambda_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "haskell_lambda_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "haskell_lambda_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "haskell_lambda_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "haskell_lambda_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
