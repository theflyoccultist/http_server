#!/usr/bin/env bash

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <path_to_html_file>"
  exit 1
fi

FILE=$1

if [ ! -f "$FILE" ]; then
  echo "$FILE does not exist."
  exit 1
fi

if [[ ! "$FILE" =~ \.html$ ]]; then
  echo "$FILE is not an HTML file."
  exit 1
fi

echo "Starting server..."

HTML_PAGE="$FILE" ./http_server
