#!/bin/bash
main(){
  (
  echo '[' 
  seq 1 1000 | while read x; do print_json_base ;done
  echo '{ "last" : "yes" }'
  echo ']'
  )> example_big.json
  (
  echo '[' 
  seq 1 1 | while read x; do print_json_base ;done
  echo '{ "last" : "yes" }'
  echo ']'
  )> example_small.json

  ln -sf example_small.json example.json
}
print_json_base(){
  cat<<'EOFF'
  {
    "_id": "57f6a42c5361b4ca58553bbb",
    "index": 0,
    "guid": "03eda1a2-3751-4410-af71-57da369b175d",
    "isActive": true,
    "balance": "$1,302.52",
    "picture": "http://placehold.it/32x32",
    "age": 34,
    "eyeColor": "brown",
    "name": {
      "first": "Roth",
      "last": "Allison"
    },
    "company": "RODEMCO",
    "email": "roth.allison@rodemco.io",
    "phone": "+1 (974) 456-2835",
    "address": "789 Murdock Court, Helen, South Dakota, 2159",
    "about": "Tempor nisi tempor enim aliquip qui excepteur. Incididunt excepteur voluptate sunt commodo. Officia aute labore quis aliquip non exercitation nulla ullamco consectetur eiusmod id. Aute officia deserunt sunt ut sint proident occaecat culpa veniam.",
    "registered": "Tuesday, December 22, 2015 6:36 PM",
    "latitude": "56.44184",
    "longitude": "-89.869975",
    "tags": [
      "sunt",
      "cillum",
      "elit",
      "cupidatat",
      "sit"
    ],
    "range": [
      0,
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9
    ],
    "friends": [
      {
        "id": 0,
        "name": "Winters Griffith"
      },
      {
        "id": 1,
        "name": "Kent William"
      },
      {
        "id": 2,
        "name": "Carrillo Roach"
      }
    ],
    "greeting": "Hello, Roth! You have 7 unread messages.",
    "favoriteFruit": "banana"
  },
  {
    "_id": "57f6a42d8b1fa6f639de0aea",
    "index": 1,
    "guid": "408b5d2b-e9b7-4aed-96ca-0b97aaad0527",
    "isActive": true,
    "balance": "$3,544.77",
    "picture": "http://placehold.it/32x32",
    "age": 27,
    "eyeColor": "green",
    "name": {
      "first": "John",
      "last": "Herring"
    },
    "company": "ORBOID",
    "email": "john.herring@orboid.us",
    "phone": "+1 (985) 488-2210",
    "address": "989 Bridge Street, Westwood, Oklahoma, 9787",
    "about": "Commodo non cupidatat est excepteur cupidatat ut aliqua dolor sunt non. Laborum occaecat nulla id cupidatat incididunt est elit ut deserunt anim nisi. Ullamco ea ullamco aliquip velit elit sint anim occaecat ex dolore sunt eiusmod consequat irure. Exercitation est sint irure adipisicing dolore nisi.",
    "registered": "Monday, September 19, 2016 4:29 PM",
    "latitude": "-64.838885",
    "longitude": "-71.78547",
    "tags": [
      "laboris",
      "ullamco",
      "magna",
      "consectetur",
      "est"
    ],
    "range": [
      0,
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9
    ],
    "friends": [
      {
        "id": 0,
        "name": "Lynda Hood"
      },
      {
        "id": 1,
        "name": "Sarah Franks"
      },
      {
        "id": 2,
        "name": "Flores Carpenter"
      }
    ],
    "greeting": "Hello, John! You have 8 unread messages.",
    "favoriteFruit": "banana"
  },
  {
    "_id": "57f6a42d11f02d1cc08765ba",
    "index": 2,
    "guid": "7464dee5-48db-4a56-b1a3-e35552abeee5",
    "isActive": true,
    "balance": "$3,665.77",
    "picture": "http://placehold.it/32x32",
    "age": 24,
    "eyeColor": "green",
    "name": {
      "first": "Gay",
      "last": "Raymond"
    },
    "company": "WATERBABY",
    "email": "gay.raymond@waterbaby.com",
    "phone": "+1 (867) 436-3614",
    "address": "919 Sheffield Avenue, Mapletown, Louisiana, 9902",
    "about": "Anim nulla qui nisi qui occaecat irure id aliqua minim. Ea veniam proident exercitation exercitation ex aliquip aute reprehenderit pariatur minim aute. Nisi aliqua culpa cillum ullamco irure nulla culpa pariatur fugiat consectetur cillum.",
    "registered": "Wednesday, July 1, 2015 11:00 AM",
    "latitude": "-46.303214",
    "longitude": "165.441024",
    "tags": [
      "tempor",
      "adipisicing",
      "reprehenderit",
      "magna",
      "occaecat"
    ],
    "range": [
      0,
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9
    ],
    "friends": [
      {
        "id": 0,
        "name": "Ortega Morin"
      },
      {
        "id": 1,
        "name": "Bonita Roberts"
      },
      {
        "id": 2,
        "name": "Pickett Sexton"
      }
    ],
    "greeting": "Hello, Gay! You have 9 unread messages.",
    "favoriteFruit": "strawberry"
  },
  {
    "_id": "57f6a42da860e70cd72c7b92",
    "index": 3,
    "guid": "4f1e2bd1-cccc-49aa-8d20-f02764769568",
    "isActive": false,
    "balance": "$2,141.70",
    "picture": "http://placehold.it/32x32",
    "age": 40,
    "eyeColor": "brown",
    "name": {
      "first": "Kelley",
      "last": "Herman"
    },
    "company": "OATFARM",
    "email": "kelley.herman@oatfarm.biz",
    "phone": "+1 (916) 525-2976",
    "address": "272 Fulton Street, Elfrida, Massachusetts, 8569",
    "about": "Nostrud tempor duis officia consequat minim Lorem voluptate excepteur nulla. Ea sint enim ut do. Officia sint aliqua pariatur adipisicing excepteur. Proident consequat non ut sint eu magna. Tempor deserunt proident ad consectetur anim consequat anim. Qui labore quis pariatur est sit cupidatat nulla mollit consectetur quis in excepteur eiusmod cillum.",
    "registered": "Tuesday, February 17, 2015 8:06 PM",
    "latitude": "-39.068081",
    "longitude": "-55.911391",
    "tags": [
      "ex",
      "proident",
      "voluptate",
      "sint",
      "eiusmod"
    ],
    "range": [
      0,
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9
    ],
    "friends": [
      {
        "id": 0,
        "name": "Franklin Blackwell"
      },
      {
        "id": 1,
        "name": "Beth Davis"
      },
      {
        "id": 2,
        "name": "Rachelle Slater"
      }
    ],
    "greeting": "Hello, Kelley! You have 5 unread messages.",
    "favoriteFruit": "apple"
  },
  {
    "_id": "57f6a42da5a71c5467920f8d",
    "index": 4,
    "guid": "e35bd259-1f4a-4eba-a9b6-cfea9c06231b",
    "isActive": true,
    "balance": "$2,706.75",
    "picture": "http://placehold.it/32x32",
    "age": 39,
    "eyeColor": "green",
    "name": {
      "first": "Gaines",
      "last": "James"
    },
    "company": "FLOTONIC",
    "email": "gaines.james@flotonic.info",
    "phone": "+1 (939) 559-3996",
    "address": "397 Lincoln Place, Lafferty, Indiana, 2166",
    "about": "Velit cillum aliqua occaecat ipsum. Fugiat dolor pariatur velit velit excepteur consequat minim culpa non proident nisi consequat consequat eu. Sunt ullamco nisi in proident occaecat ullamco laborum tempor pariatur dolore incididunt esse culpa.",
    "registered": "Saturday, January 2, 2016 5:45 PM",
    "latitude": "-68.849939",
    "longitude": "-127.540346",
    "tags": [
      "incididunt",
      "laboris",
      "culpa",
      "proident",
      "labore"
    ],
    "range": [
      0,
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9
    ],
    "friends": [
      {
        "id": 0,
        "name": "Carol Santiago"
      },
      {
        "id": 1,
        "name": "Burke Mejia"
      },
      {
        "id": 2,
        "name": "Tasha Acosta"
      }
    ],
    "greeting": "Hello, Gaines! You have 7 unread messages.",
    "favoriteFruit": "apple"
  },
  {
    "_id": "57f6a42d42264ed48979abfc",
    "index": 5,
    "guid": "88dc2fcd-31bf-4c29-b8b2-0e950e3a0ac9",
    "isActive": false,
    "balance": "$2,818.56",
    "picture": "http://placehold.it/32x32",
    "age": 37,
    "eyeColor": "green",
    "name": {
      "first": "Jeanie",
      "last": "Bullock"
    },
    "company": "XIXAN",
    "email": "jeanie.bullock@xixan.tv",
    "phone": "+1 (970) 480-3136",
    "address": "837 Ocean Parkway, Bethany, Virgin Islands, 6463",
    "about": "Exercitation exercitation laboris laboris ex elit nostrud labore elit velit amet minim. Enim quis esse ex est nisi qui consectetur sint laboris id ipsum. Aute anim occaecat aliqua ea sit.",
    "registered": "Sunday, January 31, 2016 2:31 AM",
    "latitude": "22.484752",
    "longitude": "-121.702343",
    "tags": [
      "aliquip",
      "reprehenderit",
      "exercitation",
      "cillum",
      "voluptate"
    ],
    "range": [
      0,
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9
    ],
    "friends": [
      {
        "id": 0,
        "name": "Ora Norton"
      },
      {
        "id": 1,
        "name": "Lakisha Mann"
      },
      {
        "id": 2,
        "name": "Debra Klein"
      }
    ],
    "greeting": "Hello, Jeanie! You have 6 unread messages.",
    "favoriteFruit": "strawberry"
  },
  {
    "_id": "57f6a42db6d0615c73ef1485",
    "index": 6,
    "guid": "b8c50ebf-5655-48c3-b0e1-76410660d153",
    "isActive": true,
    "balance": "$1,002.66",
    "picture": "http://placehold.it/32x32",
    "age": 28,
    "eyeColor": "brown",
    "name": {
      "first": "Hurst",
      "last": "Case"
    },
    "company": "LEXICONDO",
    "email": "hurst.case@lexicondo.net",
    "phone": "+1 (960) 481-2686",
    "address": "416 Stillwell Place, Corriganville, South Carolina, 8424",
    "about": "Fugiat elit aliqua amet officia dolor aute aliquip commodo veniam veniam minim. Cillum do reprehenderit aute reprehenderit adipisicing sit cillum enim. Mollit ut occaecat laboris qui aliqua sint labore ea amet irure magna pariatur pariatur.",
    "registered": "Friday, February 13, 2015 9:08 AM",
    "latitude": "69.524195",
    "longitude": "-107.237758",
    "tags": [
      "dolore",
      "voluptate",
      "id",
      "nulla",
      "ullamco"
    ],
    "range": [
      0,
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9
    ],
    "friends": [
      {
        "id": 0,
        "name": "Maribel Hines"
      },
      {
        "id": 1,
        "name": "Hayden Peters"
      },
      {
        "id": 2,
        "name": "Mayo Dawson"
      }
    ],
    "greeting": "Hello, Hurst! You have 6 unread messages.",
    "favoriteFruit": "banana"
  },
EOFF
}

main
