from itertools import combinations_with_replacement
import pandas as pd


flags = ['i', 'v', 'c', 'l', 'h']
files = ['test_files/dummy.c', 'test_files/Makefile']

flags_cmb = ['-'+''.join(list(set(i))) for i in list(combinations_with_replacement(flags, len(flags)))]
files_cmb = [' '.join(list(set(i))) for i in list(combinations_with_replacement(files, len(files)))]

flags_cmb = pd.DataFrame(flags_cmb).rename(columns={0: "flags_cmb"}).drop_duplicates()
files_cmb = pd.DataFrame(files_cmb).rename(columns={0: "files_cmb"}).drop_duplicates()
df = flags_cmb.merge(files_cmb, how='cross').assign(column=lambda x: x.flags_cmb + ' ' + x.files_cmb)['column']
df = pd.concat([df, files_cmb.files_cmb])

df.to_csv('full_coverage_combo.csv', index=0, header=0)
