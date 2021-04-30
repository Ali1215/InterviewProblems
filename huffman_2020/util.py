# Ali Muneer
# CCID:  amuneer

import bitio
import huffman
import pickle


def read_tree(tree_stream):
    '''Read a description of a Huffman tree from the given compressed
    tree stream, and use the pickle module to construct the tree object.
    Then, return the root node of the tree itself.

    Args:
      tree_stream: The compressed stream to read the tree from.

    Returns:
      A Huffman tree root constructed according to the given description.
    '''
    # use pickle module to load tree from file
    return pickle.load(tree_stream)

def decode_byte(tree, bitreader):
    """
    Reads bits from the bit reader and traverses the tree from
    the root to a leaf. Once a leaf is reached, bits are no longer read
    and the value of that leaf is returned.

    Args:
      bitreader: An instance of bitio.BitReader to read the tree from.
      tree: A Huffman tree.

    Returns:
      Next byte of the compressed bit stream.
    """
    if isinstance(tree, huffman.TreeLeaf):      # base case
        # if a leaf then return the value of the leaf
        return tree.getValue()
    elif isinstance(tree, huffman.TreeBranch):
        # if a branch, read one bit and traverse tree accordingly
        bit = bitreader.readbit()
        if bit == True:
              # go right if bit is True
              return decode_byte(tree.getRight(), bitreader)
        else:
              # go left if bit is false
              return decode_byte(tree.getLeft(), bitreader)
    else:
        raise TypeError('{} is not a tree type'.format(type(tree)))
    
    
          


def decompress(compressed, uncompressed):
    '''First, read a Huffman tree from the 'compressed' stream using your
    read_tree function. Then use that tree to decode the rest of the
    stream and write the resulting symbols to the 'uncompressed'
    stream.

    Args:
      compressed: A file stream from which compressed input is read.
      uncompressed: A writable file stream to which the uncompressed
          output is written.
    '''
    # read the tree from the compressed file
    tree = read_tree(compressed)

    # initialize bit reading
    readin = bitio.BitReader(compressed)
    not_end_file = True
    # initialize new file for bit writing
    writeout = bitio.BitWriter(uncompressed)
    while not_end_file:
          try:
            # recursively decode one byte
            byte = decode_byte(tree, readin)

            if byte != None:
                  writeout.writebits(byte, 8)
                  
          except EOFError:
            not_end_file = False
            # push changes to file
            writeout.flush()
    
    writeout.flush()

    
    
    



def write_tree(tree, tree_stream):
    '''Write the specified Huffman tree to the given tree_stream
    using pickle.

    Args:
      tree: A Huffman tree.
      tree_stream: The binary file to write the tree to.
    '''
    # write a huffman tree to a binary file
    pickle.dump(tree, tree_stream)
    return

def compress(tree, uncompressed, compressed):
    '''First write the given tree to the stream 'compressed' using the
    write_tree function. Then use the same tree to encode the data
    from the input stream 'uncompressed' and write it to 'compressed'.
    If there are any partially-written bytes remaining at the end,
    write 0 bits to form a complete byte.

    Flush the bitwriter after writing the entire compressed file.

    Args:
      tree: A Huffman tree.
      uncompressed: A file stream from which you can read the input.
      compressed: A file stream that will receive the tree description
          and the coded input data.
    '''
    # first write the tree to new file using pickle and initialize bitWriter on file
    write_tree(tree, compressed)
    writeout = bitio.BitWriter(compressed)

    # encoding table for compression
    table = huffman.make_encoding_table(tree)
    
    # begin reading bytes from uncompressed file
    readin = bitio.BitReader(uncompressed)
    not_end_file = True
    
    while not_end_file:
          try:
            # look up each byte in encoding table
            for x in table[readin.readbits(8)]:
                  # print out new encoded value bit by bit
                  writeout.writebit(x)
          except EOFError:
            not_end_file = False
            writeout.flush()
    writeout.flush()