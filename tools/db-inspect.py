#!/usr/bin/env python3
import os, sys
base = os.path.join('.new_db', sys.argv[1] if len(sys.argv)>1 else 'demo')
print('DB dir:', base)
for root,dirs,files in os.walk(base):
  for f in files:
    if f.endswith('.key') or f.endswith('.kv'):
      print(os.path.join(root,f))
