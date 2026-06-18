
## What can "error correcting codes" do for me? _- Their purpose_

_Error detecting codes_ (such as _CRC_ or _parity check bits_) and _error correcting codes_ are a way of encoding transmissions in a way which enables the receiver to potentially determine if an error has occurred in transmission or storage. In order to do this the length of the signal which is transmitted will be longer than the size of the message before encoding.

_Error correcting codes_ do not just detect that an error has occurred but may be able to provide a best guess for what would have been _sent_ given the signal which was _received_ without the need for retransmission from the sender.

Error correcting codes are useful in:
 - Interspace communication such on the _Voyager program_ and more recently the _Cassini–Huygens_ mission.
 - Digital communication standards such as _Digital Video Broadcasting standards (DVB-S)_.
 - Physical storage mediums such as _Compact Disks_.
 - Contemporary digital data storage such as the standard RAID level _RAID 6_.

All of these are not only examples of error correcting codes in use, but are specifically examples of where _Reed-Solomon_ codes have been used or are currently in use today.


## Ignoring the transfer phases what are the specifics? _- "messages" in Block code notation_

_This is focused on error correcting codes used in software I will only talk about information in binary form. However, a lot of the existing maths is generalised to consider non-binary based codes. I will refer to a sequence of bits which some individual wants to transfer to another as a "transmission"._

"Block codes" are a family of error correcting and error detecting codes. Many of those codes can be modelled as block codes, including Reed-Solomon codes.

All block codes need to define the "message length".

A "message" is a fixed length of binary data, which when transferred as part of this error correcting code have the property that any errors which occur while transferring information related to that "message" will have no impact on the ability to decode any of the other "messages".

_Ignoring what happens on the wire_ error correcting codes work by taking an individual "message", encoding that into some binary pieces of data to be transferred or stored, then attempting to decode the binary data it receives back into a "message".

It is not mathematically possible for any possible received signal to provide a single best guess for what would have been sent. In those circumstances it will be known that an error has occurred, like for error detecting codes, and alternatives exist such as providing a list of the equally most likely sent signals can be provided without needing to communicate with the sender.


## How is the encoded form modelled? _- "alphabets" and "blocks" in block code notation_

The encoded form of a message is also divided up into self-contained sections which are called elements of an "alphabet". The "alphabet" is referred to as a set of size `q`, and here there will be some `w` such that `q = 2**w`.

The encoded form of a "message" is known as a "codeword" and will be a sequence of `n` "alphabet" entries. Any sequence of `n` "alphabet" entries is known as a "block".

Not all "blocks" correspond to "encoded messages". All received signals will be modelled as "blocks".

During transmission if at one error occurs within an "alphabet entries" within a "codeword" then any number of errors may occur within that "alphabet entry" without making the corresponding "received signal" harder to decode than if only one error occurred within that "alphabet entry".


    Because of this "block codes" are referred to as dealing well with burst errors, because a series of contiguous error bits within the transmission of a codeword are handled better than if that same number of errors were spread out into different alphabet entries within the codeword.
    
    There is no reason why you need to transfer an encoded error-correcting code as a contiguous series of bits, so if you would like to you can transfer alphabet entries from different codewords one after another across the wire, and further adjustments can be made to accommodate for a specific anticipated error form.

The Hamming distance between two blocks is the number of alphabet entries by which two blocks differ. `d` is the minimum Hamming distance between any two possible codewords within a block code.


## Revisiting message as a series of alphabet entries _- block code notation_

To revisit the previous definition of a "message" - a "message" is also modelled as an ordered set of "alphabet" entries, but of length `k`.

In order for an error correcting code to be able to detect any errors we need to have that `n > k`.

`d =< n-k+1` for all block codes. Therefore, block codes for which `d = n-k+1` equal the theoretical higher bound of `d` with respect to `n` and `k` and is known as a Maximum Distance Separable Code (an _MDS_ code).

This has led to the common notation that a block code with alphabet size `q`, message length `k`, block length `n` and minimum hamming distance `d` is expressed with the following notation: `(n,k,d)q`.


## How are errors corrected? _- How can this be used to measure how many errors an individual encoded transmission can withstand?_

The way in which error correcting and error detecting codes can detect errors is that we know before-hand all possible codewords. When a block is received as a signal decoding works by finding the codeword for which the Hamming distance between that signal and the codeword is as small as possible. From there the message which produced that codeword can be found (because the encoding function must be injective this message is unique).

This is significant because given a block we want to find the message which maximises the probability of that message having been sent given the block we received. If we assume all messages are equally likely to be sent and that the probability of an individual alphabet entry being received as an error is less than 50%, independent, and uniformly distributed then the message which corresponds to the codeword with smallest hamming distance from the received block will be that message. This is a heuristic which is applied, however scenarios where this isn't the case may be able to take advantage of other methodologies.

This also explains why messages which endured errors during transmission may arrive in a form which is decoded decoded into a different message, or less probably, appears as if no error occurred.

There is only guaranteed to be precisely one codeword with minimum Hamming distance from a block if the minimum distance between that block and a codeword is equal to `floor((d-1)/2)` where `floor` is a function which rounds a fraction down to the closest integer. This value is known as `e` and for all block codes `e = floor((d-1)/2)`.

