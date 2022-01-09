# CRC-Implementation-in-C
## PROBLEM STATEMENT
A program to calculate CRC for a given stream of data and calculations of CRC has to be done using three methods
- CRC using bit-by-bit method
- CRC using byte-by-byte method
- An improved version of byte by byte
And finally measure the timing for each method
 
 ## THEORY
 
Cyclic Redundancy Check (CRC) is a block code invented by W. Wesley Peterson in 1961. It is commonly used to detect accidental changes to data transmitted via telecommunications networks and storage devices.
CRC involves binary division of the data bits being sent by a predetermined divisor agreed upon by the communicating system. The divisor is generated using polynomials. So, CRC is also called polynomial code checksum.
![image](https://user-images.githubusercontent.com/86975877/148676751-253ab72b-7781-4402-90a5-ccb9d4687fae.png)

#### Encoding using CRC
- The communicating parties agrees upon the size of message block and the CRC divisor. For example, the block chosen may be CRC (7, 4), where 7 is the total length of the block and 4 is the number of bits in the data segment. The divisor chosen may be 1011.
- The sender performs binary division of the data segment by the divisor.
- It then appends the remainder called CRC bits to the end of data segment. This makes the resulting data unit exactly divisible by the divisor.

#### Decoding
- The receiver divides the incoming data unit by the divisor.
- If there is no remainder, the data unit is assumed to be correct and is accepted.
- Otherwise, it is understood that the data is corrupted and is therefore rejected. The receiver may then send an erroneous acknowledgement back to the sender for retransmission.

![image](https://user-images.githubusercontent.com/86975877/148676782-f0b83103-6bb2-43c1-80b8-520f59b03673.png)

1. BIT BY BIT IMPLEMENTATION
    -Call the uppermost c+1 bits of the message the remainder
   - Beginning with the most significant bit in the original message and for each bit position that follows, look at the c+1 bit remainder:
   - If the most significant bit of the remainder is a one, the divisor is said to divide into it. If that happens (just as in any other long division) it is necessary to indicate a successful division in the appropriate bit position in the quotient and to compute the new remainder. In the case of modulo-2 binary division, we simply:
     - Set the appropriate bit in the quotient to a one, and
     - XOR the remainder with the divisor and store the result back into the remainder
   - Otherwise (if the first bit is not a one):
     - Set the appropriate bit in the quotient to a zero, and
     - XOR the remainder with zero (no effect)
   - Left-shift the remainder, shifting in the next bit of the message. The bit that's shifted out will always be a zero, so no information is lost.
   - The final value of the remainder is the CRC of the given message.
  
 2. BYTE BY BYTE IMPLEMENTATION
        The most common way to improve the efficiency of the CRC calculation is to throw memory at the problem. For a given input remainder and generator polynomial, the output remainder will always be the same. So, it's possible to precompute the output remainder for each of the possible byte-wide input remainders and store the results in a lookup table. That lookup table can then be used to speed up the CRC calculations for a given message. The speedup is realized because the message can now be processed byte by byte, rather than bit by bit.
         The code to precompute the output remainders for each possible input byte is shown in Listing 3. The computed remainder for each possible byte-wide dividend is stored in the array crcTable[]. In practice, the crcInit() function could either be called during the target's initialization sequence (thus placing crcTable[] in RAM) or it could be run ahead of time on your development workstation with the results stored in the target device's ROM.

3. IMPROVED BYTE BY BYTE IMPLEMENTATION
          Consider a message that begins with some number of zero bits. The remainder will never contain anything other than zero until the first one in the message is shifted into it. That's a dangerous situation, since packets beginning with one or more zeros may be completely legitimate and a dropped or added zero would not be noticed by the CRC. (In some applications, even a packet of all zeros may be legitimate!) The simple way to eliminate this weakness is to start with a nonzero remainder. The parameter called initial remainder tells you what value to use for a particular CRC standard. And only one small change is required to the crcSlow() and crcFast() functions:
```
crc remainder = INITIAL_REMAINDER 
```
          The final XOR value exists for a similar reason. To implement this capability, simply change the value that's returned by crcSlow() and crcFast() as follows:
