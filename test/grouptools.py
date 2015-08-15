import itertools

def grouper(iterable, n, fillvalue=None):
    "Collect data into fixed-length chunks or blocks"
    # grouper('ABCDEFG', 3, 'x') --> ABC DEF Gxx
    args = [iter(iterable)] * n
    return itertools.izip_longest(fillvalue=fillvalue, *args)

def groupfiles( files, njobs ) :
    nfiles = len(files)
    filesPerJob = nfiles / ( njobs - 1)
    groups = list ( grouper(files, filesPerJob, '' ) 

