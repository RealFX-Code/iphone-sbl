#   
#   SPDX-License-Identifier: GPL-3.0-or-later
#   SPDX-FileCopyrightText: 2026 Leah <leah@realfx.rocks>
#   
#   With help from clanker
#

import struct, sys

data = open(sys.argv[1], "rb").read()
# Pad DATA payload to 4-byte alignment
padded = data + b"\x00" * ((4 - len(data) % 4) % 4)

# DATA tag: magic 'DATA' (LE: b'ATAD'), total_size, data_size
data_tag = struct.pack("<4sII", b"ATAD", 12 + len(padded), len(data)) + padded
# IMG3 header: magic 'IMG3' (LE: b'3gmI'), full_size, packed_size, shsh_offset, ident 'ibss' (LE: b'ssbi')
img3_hdr = struct.pack("<4sIII4s", b"3gmI", 20 + len(data_tag), len(data_tag), 0, b"ssbi")

open(sys.argv[2], "wb").write(img3_hdr + data_tag)
