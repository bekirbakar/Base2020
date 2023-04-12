import sys
import audioread

"""
This script contains functions to work with audio files and durations. The
`audio_file_properties` function takes an audio file path as input and displays
its duration in minutes and seconds. The `duration_converter` function takes a
duration in seconds and converts it into hours, minutes, and seconds. The script
accepts a duration in seconds as a command-line argument and demonstrates the
use of the `duration_converter` function.
"""


def audio_file_properties(file):
    """
    Display the duration of an audio file in minutes and seconds.
    
    :param file: The path to the audio file.
    """
    with audioread.audio_open(file) as f:
        seconds = f.duration
        m, s = divmod(seconds, 60)
        print(seconds)
        print(m, s)


def duration_converter(length):
    """
    Convert the given duration in seconds to hours, minutes, and seconds.
    
    :param length: The duration in seconds.
    :return: A tuple containing hours, minutes, and seconds.
    """
    hours = length // 3600
    length %= 3600

    mins = length // 60
    length %= 60

    seconds = length

    return hours, mins, seconds


if __name__ == "__main__":
    input_data = float(sys.argv[1])
    print(input_data)

    print(duration_converter(input_data))
