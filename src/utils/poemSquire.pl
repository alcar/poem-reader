# Tries to conjugate a verb in its infinitive form.
#
# Params
# {string} word: the target verb (hopefully).
# {number} attempts: the number of previous attempts.
#
# Output
# {(string|undef)} the conjugated verb.
sub getInfinitiveForm {
  my ($word, $attempts) = @_;

  # Verbs in the ~ing form
  if ($word =~ /^[a-z]+ing$/i) {
    ## that came from a generic verb
    if ($attempts < 1) {
      return substr($word, 0, -3);
    }

    ## that came from a verb that ends in ~e
    if ($attempts < 2) {
      return substr($word, 0, -3) . "e";
    }

    ## that got an extra consonant when conjugated
    if ($attempts < 3) {
      return substr($word, 0, -4);
    }

    return undef;
  }

  # Verbs in the ~ed form (general case)
  if ($word =~ /^[a-z]+[^li]ed$/i) {
    ## that came from a verb that ends in ~e
    if ($attempts < 1) {
      return substr($word, 0, -1);
    }

    ## that came from a generic verb
    if ($attempts < 2) {
      return substr($word, 0, -2);
    }

    ## that got an extra consonant when conjugated
    if ($attempts < 3) {
      return substr($word, 0, -4);
    }

    return undef;
  }

  # Single-attempt cases

  if ($attempts > 0) {
    return undef;
  }

  ## Verbs in the ~ed form that came from a verb that ends in vowel + l
  if ($word =~ /^[a-z]*[aeiou]lled$/i) {
    return substr($word, 0, -3);
  }

  ## Verbs in either the ~ed form or the third person singular present simple
  # form that came from a verb that ends in ~y
  if ($word =~ /^[a-z]+ie(d|s)$/i) {
    return substr($word, 0, -3) . "y";
  }

  ## Verbs in the third person singular present simple form that end in ~es
  if ($word =~ /^[a-z]+es$/i) {
    return substr($word, 0, -2);
  }

  ## Verbs in the third person singular present simple form that end in ~s
  if ($word =~ /^[a-z]+s$/i) {
    return substr($word, 0, -1);
  }
}

# Tries to find the meaning of a word in a list.
#
# Params
# {string} word: the target word.
# {string[]} meaningList: a list containing words and their respective meanings.
#
# Output
# {(string|undef)} the meaning of the word.
sub getMeaningFromList {
  my ($word, @meaningList) = @_;

  my @foundEntries = grep(m/^\Q$word:/i, @meaningList);

  return $foundEntries[0];
}

# Tries to conjugate a noun in its singular form.
#
# Params
# {string} word: the target noun (hopefully).
# {number} attempts: the number of previous attempts.
#
# Output
# {(string|undef)} the conjugated noun.
sub getSingularForm {
  my ($word, $attempts) = @_;

  # Nouns that end in ~ves
  if ($word =~ /^[a-z]+ves$/i) {
    ## and came from a noun that ends in ~f
    if ($attempts < 1) {
      return substr($word, 0, -3) . "f";
    }

    ## and came from a noun that ends in ~fe
    if ($attempts < 2) {
      return substr($word, 0, -3) . "fe"
    }

    return undef;
  }

  # Nouns that end in ~s
  if ($word =~ /^[a-z]+s$/i) {
    ## and came from a generic noun
    if ($attempts < 1) {
      return substr($word, 0, -1);
    }

    ## and also end in "~es"
    if ($word =~ /^[a-z]+es$/i) {
      ### and came from a noun that ends in ~s | ~ss | ~sh | ~ch | ~x | ~z | ~o
      if ($attempts < 2) {
        return substr($word, 0, -2);
      }

      ### and came from a noun that ends in ~is
      if ($attempts < 3) {
        return substr($word, 0, -2) . "is";
      }

      ### and got an extra "s" or "z" when pluralized
      if ($word =~ /^[a-z]+(ss|zz)es$/i && $attempts < 4) {
        return substr($word, 0, -3);
      }

      return undef;
    }

    return undef;
  }

  # Single-attempt cases

  if ($attempts > 0) {
    return undef;
  }

  ## Nouns that end in ~ies
  if ($word =~ /^[a-z]+ies$/i) {
    return substr($word, 0, -3) . "y";
  }


  ## Nouns that end in ~i
  if ($word =~ /^[a-z]+i$/i) {
    return substr($word, 0, -1) . "us";
  }

  ## Nouns that end in ~a
  if ($word =~ /^[a-z]+a$/i) {
    return substr($word, 0, -1) . "on";
  }
}

# Tries to find the meaning of a word.
#
# Params
# {string} word: the target word.
#
# Output
# {(string|undef)} the meaning of the word.
sub getWordMeaning {
  my $word = $_[0];

  # Reads and stores all entries from the dictionary
  open(my $dictionary, "<", "dictionary.txt") or die("Can't open dictionary.txt.\nError: $!.");

  my @meaningList = <$dictionary>;

  close($dictionary) or die("Can't close dictionary.txt.\nError: $!.");

  my $meaning;

  # Attempts to get the meaning of the word as is
  $meaning = getMeaningFromList($word, @meaningList);

  if ($meaning) {
    return $meaning;
  }

  # Assumes the word is a verb and tries to get its infinitive form
  my $attempts = 0;
  my $infinitiveVerb;

  do {
    $infinitiveVerb = getInfinitiveForm($word, $attempts);

    $attempts += 1;

    if ($infinitiveVerb) {
      $meaning = getMeaningFromList($infinitiveVerb, @meaningList);
    }
  } while (!$meaning && $infinitiveVerb);

  if ($meaning) {
    return $meaning;
  }

  # Assumes the word is a noun and tries to get its singular form
  $attempts = 0;
  my $singularNoun;

  do {
    $singularNoun = getSingularForm($word, $attempts);

    $attempts += 1;

    if ($singularNoun) {
      $meaning = getMeaningFromList($singularNoun, @meaningList);
    }
  } while (!$meaning && $singularNoun);

  if ($meaning) {
    return $meaning;
  }
}

# Splits a verse into words and removes its special characters.
#
# Params
# {string} verse: the target verse.
#
# Output
# {string[]} a list containing the words from the verse.
sub getWordsFromVerse {
  my $verse = $_[0];

  # Removes special characters and 's/’s contractions
  my $partiallyCleanVerse = $verse =~ s/('|’)s|[^a-z]/ /igr;
  my $cleanVerse = $partiallyCleanVerse =~ s/(^ +\b)|(\b +$)//gr;

  return split(/\b +\b/, $cleanVerse);
}

# Returns whether or not a file is a text file.
#
# Params
# {string} fileName: the file name.
#
# Output
# {0|1} 1 if it's a text file, otherwise 0.
sub isTextFile {
  my $fileName = $_[0];

  # A text file is a file with the ".txt" (or ".TXT") extension
  return $fileName =~ /^[^\/]+\.((txt)|(TXT))$/;
}
