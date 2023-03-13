original_canvas = null;
original_ctx = null;
tiles_canvas = null;
tiles_ctx = null;
final_palette_canvas = null;
final_palette_ctx = null;
palettes_canvas = null;
palettes_ctx = null;
selected_tile_canvas = null;
selected_tile_ctx = null;
unique_colors = new Array();
unique_colors_counter = new Array();
unique_sorted_colors = new Array();
image_loaded = false;
var original_image = null;
var tiles = [];
var tiles_canvas_down = false;

tile_canvas_buttons = [
  {x: 300, y: 10, w: 300, h: 30,
   mouse_out: function(){},
   mouse_over: function(){},
   on_mouse_down: function() {},
   on_mouse_up: function() {},
   button_state: false},
];

var g1_color_1 = null;
var g1_color_2 = null;
var g1_color_3 = null;
var g1_color_4 = null;

var g1_final_palette_color_1 = "white";
var g1_final_palette_color_2 = "white";
var g1_final_palette_color_3 = "white";
var g1_final_palette_color_4 = "white";
var g2_final_palette_color_1 = "white";
var g2_final_palette_color_2 = "white";
var g2_final_palette_color_3 = "white";
var g2_final_palette_color_4 = "white";
var g3_final_palette_color_1 = "white";
var g3_final_palette_color_2 = "white";
var g3_final_palette_color_3 = "white";
var g3_final_palette_color_4 = "white";
var g4_final_palette_color_1 = "white";
var g4_final_palette_color_2 = "white";
var g4_final_palette_color_3 = "white";
var g4_final_palette_color_4 = "white";
var g5_final_palette_color_1 = "white";
var g5_final_palette_color_2 = "white";
var g5_final_palette_color_3 = "white";
var g5_final_palette_color_4 = "white";
var g6_final_palette_color_1 = "white";
var g6_final_palette_color_2 = "white";
var g6_final_palette_color_3 = "white";
var g6_final_palette_color_4 = "white";
var g7_final_palette_color_1 = "white";
var g7_final_palette_color_2 = "white";
var g7_final_palette_color_3 = "white";
var g7_final_palette_color_4 = "white";

function init() {
  original_canvas = document.getElementById("png");
  original_canvas.width  = document.getElementById('png_holder').clientWidth;
  original_canvas.height = document.getElementById('png_holder').clientHeight;
  original_ctx = original_canvas.getContext('2d');
  original_ctx.fillStyle='black';
  original_ctx.scale(2,2);
  original_ctx.imageSmoothingEnabled = false;
  original_ctx.fillRect(0,0,original_canvas.width,original_canvas.height);

  tiles_canvas = document.getElementById("tiles");
  tiles_ctx = tiles_canvas.getContext('2d', { willReadFrequently: true });
  tiles_ctx.fillStyle='black';
  tiles_ctx.scale(1,1);
  tiles_ctx.imageSmoothingEnabled = false;
  tiles_ctx.fillRect(0,0,tiles_canvas.width,tiles_canvas.height);

  palettes_canvas = document.getElementById("palettes");
  palettes_canvas.width  = document.getElementById('palettes_holder').clientWidth;
  palettes_ctx = palettes_canvas.getContext('2d');
  palettes_ctx.fillStyle='#121212';
  palettes_ctx.imageSmoothingEnabled = false;
  palettes_ctx.fillRect(0,0,palettes_canvas.width,palettes_canvas.height);

  selected_tile_canvas = document.getElementById("selected_tile");
  selected_tile_canvas.width  = document.getElementById('selected_tile_holder').clientWidth;
  selected_tile_ctx = selected_tile_canvas.getContext('2d', { willReadFrequently: true });
  selected_tile_ctx.fillStyle='#6a6a6a';
  selected_tile_ctx.imageSmoothingEnabled = false;
  selected_tile_ctx.fillRect(0,0,selected_tile_canvas.width,selected_tile_canvas.height);

  final_palette_canvas = document.getElementById("final_palette");
  final_palette_canvas.width  = document.getElementById('palette_menu').clientWidth;
  final_palette_canvas.height = document.getElementById('palette_menu').clientHeight;
  final_palette_ctx = final_palette_canvas.getContext('2d');
  final_palette_ctx.fillStyle='#121212';
  final_palette_ctx.imageSmoothingEnabled = false;
  final_palette_ctx.fillRect(0,0,final_palette_canvas.width,final_palette_canvas.height);

  palettes_ctx.font = "20px Helvetica";
  palettes_ctx.fillStyle = "white";
  palettes_ctx.fillText("Original Picture Colors", 15, 30);

  palettes_canvas.onmousemove = function(e) {

    // important: correct mouse position:
    var rect = this.getBoundingClientRect(),
        x = e.clientX - rect.left,
        y = e.clientY - rect.top,
        i = 0, r;
        button = e.which


    while(r = tile_canvas_buttons[i++]) {
      palettes_ctx.beginPath();
      palettes_ctx.rect(r.x, r.y, r.w, r.h);
      var over = palettes_ctx.isPointInPath(x, y) ? true : false;
      if (over) {
        r.mouse_over();

      } else {
        r.mouse_out();
      }
    }
  };

  palettes_canvas.onmousedown = function(e) {

    // important: correct mouse position:
    var rect = this.getBoundingClientRect(),
        x = e.clientX - rect.left,
        y = e.clientY - rect.top,
        i = 0, r;
        button = e.which


    while(r = tile_canvas_buttons[i++]) {
      palettes_ctx.beginPath();
      palettes_ctx.rect(r.x, r.y, r.w, r.h);
      var over = palettes_ctx.isPointInPath(x, y) ? true : false;
      if (over) {
        r.on_mouse_down();
      }
    }
  };

  palettes_canvas.onmouseup = function(e) {

    // important: correct mouse position:
    var rect = this.getBoundingClientRect(),
        x = e.clientX - rect.left,
        y = e.clientY - rect.top,
        i = 0, r;
        button = e.which


    while(r = tile_canvas_buttons[i++]) {
      r.on_mouse_up();
    }
  };

  document.getElementById('image_file').onchange = function (evt) {
    var tgt = evt.target || window.event.srcElement,
        files = tgt.files;

    // FileReader support
    if (FileReader && files && files.length) {
        var fr = new FileReader();
        fr.onload = () => showImage(fr);
        fr.readAsDataURL(files[0]);
    }
  }

  tiles_canvas.onmousedown = function(e) {
    if (tiles_canvas_down == true) {
      return;
    }

    // important: correct mouse position:
    var rect = this.getBoundingClientRect(),
        x = e.clientX - rect.left,
        y = e.clientY - rect.top,
        i = 0, r;
        button = e.which

    var tile_x = parseInt(x/9)
    var tile_y = parseInt(y/9)

    renderSelectedTile(tile_x, tile_y);

    tiles_canvas_down = true;
  };

  tiles_canvas.onmouseup = function(e) {
    tiles_canvas_down = false;
  };

  g1_color_1 = document.getElementById("g1_final_color_1");
  g1_color_1.addEventListener("input", function(){
    g1_final_palette_color_1 = g1_color_1.value;
    showFinalPalette();
  }, false);
  g1_color_2 = document.getElementById("g1_final_color_2");
  g1_color_2.addEventListener("input", function(){
    g1_final_palette_color_2 = g1_color_2.value;
    showFinalPalette();
  }, false);
  g1_color_3 = document.getElementById("g1_final_color_3");
  g1_color_3.addEventListener("input", function(){
    g1_final_palette_color_3 = g1_color_3.value;
    showFinalPalette();
  }, false);
  g1_color_4 = document.getElementById("g1_final_color_4");
  g1_color_4.addEventListener("input", function(){
    g1_final_palette_color_4 = g1_color_4.value;
    showFinalPalette();
  }, false);
  g2_color_1 = document.getElementById("g2_final_color_1");
g2_color_1.addEventListener("input", function(){
  g2_final_palette_color_1 = g2_color_1.value;
  showFinalPalette();
}, false);
g2_color_2 = document.getElementById("g2_final_color_2");
g2_color_2.addEventListener("input", function(){
  g2_final_palette_color_2 = g2_color_2.value;
  showFinalPalette();
}, false);
g2_color_3 = document.getElementById("g2_final_color_3");
g2_color_3.addEventListener("input", function(){
  g2_final_palette_color_3 = g2_color_3.value;
  showFinalPalette();
}, false);
g2_color_4 = document.getElementById("g2_final_color_4");
g2_color_4.addEventListener("input", function(){
  g2_final_palette_color_4 = g2_color_4.value;
  showFinalPalette();
}, false);
g3_color_1 = document.getElementById("g3_final_color_1");
g3_color_1.addEventListener("input", function(){
  g3_final_palette_color_1 = g3_color_1.value;
  showFinalPalette();
}, false);
g3_color_2 = document.getElementById("g3_final_color_2");
g3_color_2.addEventListener("input", function(){
  g3_final_palette_color_2 = g3_color_2.value;
  showFinalPalette();
}, false);
g3_color_3 = document.getElementById("g3_final_color_3");
g3_color_3.addEventListener("input", function(){
  g3_final_palette_color_3 = g3_color_3.value;
  showFinalPalette();
}, false);
g3_color_4 = document.getElementById("g3_final_color_4");
g3_color_4.addEventListener("input", function(){
  g3_final_palette_color_4 = g3_color_4.value;
  showFinalPalette();
}, false);
g4_color_1 = document.getElementById("g4_final_color_1");
g4_color_1.addEventListener("input", function(){
  g4_final_palette_color_1 = g4_color_1.value;
  showFinalPalette();
}, false);
g4_color_2 = document.getElementById("g4_final_color_2");
g4_color_2.addEventListener("input", function(){
  g4_final_palette_color_2 = g4_color_2.value;
  showFinalPalette();
}, false);
g4_color_3 = document.getElementById("g4_final_color_3");
g4_color_3.addEventListener("input", function(){
  g4_final_palette_color_3 = g4_color_3.value;
  showFinalPalette();
}, false);
g4_color_4 = document.getElementById("g4_final_color_4");
g4_color_4.addEventListener("input", function(){
  g4_final_palette_color_4 = g4_color_4.value;
  showFinalPalette();
}, false);
g5_color_1 = document.getElementById("g5_final_color_1");
g5_color_1.addEventListener("input", function(){
  g5_final_palette_color_1 = g5_color_1.value;
  showFinalPalette();
}, false);
g5_color_2 = document.getElementById("g5_final_color_2");
g5_color_2.addEventListener("input", function(){
  g5_final_palette_color_2 = g5_color_2.value;
  showFinalPalette();
}, false);
g5_color_3 = document.getElementById("g5_final_color_3");
g5_color_3.addEventListener("input", function(){
  g5_final_palette_color_3 = g5_color_3.value;
  showFinalPalette();
}, false);
g5_color_4 = document.getElementById("g5_final_color_4");
g5_color_4.addEventListener("input", function(){
  g5_final_palette_color_4 = g5_color_4.value;
  showFinalPalette();
}, false);
g6_color_1 = document.getElementById("g6_final_color_1");
g6_color_1.addEventListener("input", function(){
  g6_final_palette_color_1 = g6_color_1.value;
  showFinalPalette();
}, false);
g6_color_2 = document.getElementById("g6_final_color_2");
g6_color_2.addEventListener("input", function(){
  g6_final_palette_color_2 = g6_color_2.value;
  showFinalPalette();
}, false);
g6_color_3 = document.getElementById("g6_final_color_3");
g6_color_3.addEventListener("input", function(){
  g6_final_palette_color_3 = g6_color_3.value;
  showFinalPalette();
}, false);
g6_color_4 = document.getElementById("g6_final_color_4");
g6_color_4.addEventListener("input", function(){
  g6_final_palette_color_4 = g6_color_4.value;
  showFinalPalette();
}, false);
g7_color_1 = document.getElementById("g7_final_color_1");
g7_color_1.addEventListener("input", function(){
  g7_final_palette_color_1 = g7_color_1.value;
  showFinalPalette();
}, false);
g7_color_2 = document.getElementById("g7_final_color_2");
g7_color_2.addEventListener("input", function(){
  g7_final_palette_color_2 = g7_color_2.value;
  showFinalPalette();
}, false);
g7_color_3 = document.getElementById("g7_final_color_3");
g7_color_3.addEventListener("input", function(){
  g7_final_palette_color_3 = g7_color_3.value;
  showFinalPalette();
}, false);
g7_color_4 = document.getElementById("g7_final_color_4");
g7_color_4.addEventListener("input", function(){
  g7_final_palette_color_4 = g7_color_4.value;
  showFinalPalette();
}, false);
showFinalPalette();
}

function showImage(fileReader) {
  var img = document.getElementById("hidden_image");
  img.onload = () => {
    getImageData(img);
    showTiles(img, 1);
    showFinalPalette();
    image_loaded = true;
  }
  img.src = fileReader.result;
}

function getImageData(img) {
  original_image = img;
  original_ctx.drawImage(original_image, 0, 0);
}

function showTiles(img, scale) {
  tile_size = 8 * scale
  culmulative_width = 0;
  culmulative_height = 0;
  space = (1 * scale)
  for (var i = 0; i < img.width/tile_size; i++) {
    culmulative_width += 8;
    culmulative_height = 0;
    tiles[i] = []
    for (var j = 0; j < img.height/tile_size; j++) {
      culmulative_height += 8;
      tiles_ctx.drawImage(img, i*tile_size, j*tile_size, tile_size,
                          tile_size, i*(tile_size + space), j*(tile_size + space), tile_size, tile_size);
      tiles[i][j] = tiles_ctx.getImageData(i*(tile_size + space), j*(tile_size + space), 8, 8)
    }
  }
}

function showPalettes(tile_x, tile_y) {
  palettes_ctx.fillStyle='#121212';
  palettes_ctx.imageSmoothingEnabled = false;
  palettes_ctx.fillRect(0,0,palettes_canvas.width,palettes_canvas.height);

  unique_colors = []
  unique_sorted_colors = []
  unique_colors_counter = []
  imageData = tiles[tile_y][tile_x].data;

  for (var i = 0; i < imageData.length; i+=4) {
    var entry = [imageData[i], imageData[i+1], imageData[i+2]];
    if (containsObject(entry, unique_colors) == false) {
      unique_colors.push(entry)
      unique_colors_counter.push({color:entry, counter:1});
    } else {
      var index = findObject(entry, unique_colors_counter);
      if (index >= 0) {
        unique_colors_counter[index].counter++;
      }
    }
  }

  unique_sorted_colors = unique_colors.map(function(c, i) {
    // Convert to HSL and keep track of original indices
    return {color: rgbToHsl(c), index: i};
  }).sort(function(c1, c2) {
    // Sort by hue
    return c1.color[0] - c2.color[0];
  }).map(function(data) {
    // Retrieve original RGB color
    return unique_colors[data.index];
  });

  var horizontal_counter = 20;
  var vertical_counter = 50;
  for (var i = 0; i < unique_sorted_colors.length; i++) {
    palettes_ctx.fillStyle = `rgba(${unique_sorted_colors[i][0]}, ${unique_sorted_colors[i][1]}, ${unique_sorted_colors[i][2]}, 1)`;
    palettes_ctx.fillRect(horizontal_counter, vertical_counter, 100, 100);

    palettes_ctx.fillStyle = `rgba(0, 0, 0, 255)`;
    palettes_ctx.fillRect(horizontal_counter + 69, vertical_counter + 69, 31, 31);

    palettes_ctx.fillStyle = `rgba(255, 255, 255, 255)`;
    palettes_ctx.fillRect(horizontal_counter + 70, vertical_counter + 70, 30, 30);

    var index = findObject(unique_sorted_colors[i], unique_colors_counter);
      if (index >= 0) {
        palettes_ctx.font="10px helvetica";
        palettes_ctx.shadowColor="black";
        palettes_ctx.shadowBlur = 3;
        palettes_ctx.lineWidth = 2;
        palettes_ctx.strokeText(unique_colors_counter[index].counter, horizontal_counter + 5, vertical_counter + 15);
        palettes_ctx.shadowBlur = 0;
        palettes_ctx.fillStyle="white";
        palettes_ctx.fillText(unique_colors_counter[index].counter, horizontal_counter + 5, vertical_counter + 15);
      }

    horizontal_counter += 110;
    if (horizontal_counter >= palettes_canvas.width || horizontal_counter + 100 >= palettes_canvas.width) {
      vertical_counter += 110;
      horizontal_counter = 20;
    }
  }
}

function showFinalPalette() {
  var horizontal_counter = 120;
  var vertical_counter = 20;
  var colors = [
                [g1_final_palette_color_1, g1_final_palette_color_2, g1_final_palette_color_3, g1_final_palette_color_4],
                [g2_final_palette_color_1, g2_final_palette_color_2, g2_final_palette_color_3, g2_final_palette_color_4],
                [g3_final_palette_color_1, g3_final_palette_color_2, g3_final_palette_color_3, g3_final_palette_color_4],
                [g4_final_palette_color_1, g4_final_palette_color_2, g4_final_palette_color_3, g4_final_palette_color_4],
                [g5_final_palette_color_1, g5_final_palette_color_2, g5_final_palette_color_3, g5_final_palette_color_4],
                [g6_final_palette_color_1, g6_final_palette_color_2, g6_final_palette_color_3, g6_final_palette_color_4],
                [g7_final_palette_color_1, g7_final_palette_color_2, g7_final_palette_color_3, g7_final_palette_color_4]
              ]
  for (var j = 0; j < 7; j++) {
    for (var i = 0; i < 4; i++) {

      final_palette_ctx.font = "20px Helvetica";
      final_palette_ctx.fillStyle = "white";
      final_palette_ctx.fillText(`Palette ${j}`, 15, vertical_counter + 30);

      final_palette_ctx.fillStyle = colors[j][i]
      final_palette_ctx.fillRect(horizontal_counter, vertical_counter, 50, 50);

      final_palette_ctx.font="10px helvetica";
      final_palette_ctx.shadowColor="black";
      final_palette_ctx.shadowBlur = 3;
      final_palette_ctx.lineWidth = 2;
      final_palette_ctx.strokeText(i, horizontal_counter + 5, vertical_counter + 15);
      final_palette_ctx.shadowBlur = 0;
      final_palette_ctx.fillStyle="white";
      final_palette_ctx.fillText(i, horizontal_counter + 5, vertical_counter + 15);

      horizontal_counter += 60;
    }
    vertical_counter += 80;
    horizontal_counter = 120;
  }
}

function remap_colors() {
  var currentX = 0;
  var currentY = 0;
  const image_data = original_ctx.getImageData(currentX, currentY, 8, 8);

  for (var i = 0; i < 8; i++) {
    for (var j = 0; j < 8; j++) {
      var offset = (j * original_image.width + i) * 4;

    }
  }

  original_ctx.putImageData(image_data, 0, 0);
  showTiles(original_canvas, 1)
}

function containsObject(obj, list) {
  var i;
  for (i = 0; i < list.length; i++) {
      if (list[i][0] === obj[0] &&
          list[i][1] === obj[1] &&
          list[i][2] === obj[2]) {
          return true;
      }
  }
  return false;
}

function findObject(obj, list) {
  var i;
  if (list.length != 0) {
    for (i = 0; i < list.length; i++) {
        if (list[i].color[0] === obj[0] &&
            list[i].color[1] === obj[1] &&
            list[i].color[2] === obj[2]) {
            return i;
        }
    }
  }
  return -1;
}

function colorDistance(color1, color2) {
  const x =
    Math.pow(color1[0] - color2[0], 2) +
    Math.pow(color1[1] - color2[1], 2) +
    Math.pow(color1[2] - color2[2], 2);
  return Math.sqrt(x);
}

function rgbToHsl(c) {
  var r = c[0]/255, g = c[1]/255, b = c[2]/255;
  var max = Math.max(r, g, b), min = Math.min(r, g, b);
  var h, s, l = (max + min) / 2;

  if(max == min) {
    h = s = 0; // achromatic
  } else {
    var d = max - min;
    s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
    switch(max){
      case r: h = (g - b) / d + (g < b ? 6 : 0); break;
      case g: h = (b - r) / d + 2; break;
      case b: h = (r - g) / d + 4; break;
    }
    h /= 6;
  }
  return new Array(h * 360, s * 100, l * 100);
}

function renderSelectedTile(tile_x, tile_y) {
  selected_tile_ctx.fillStyle='#6a6a6a';
  selected_tile_ctx.fillRect(0,0,selected_tile_canvas.width,selected_tile_canvas.height);
  var ci = tiles_ctx.getImageData(tile_x*9,tile_y*9, 8, 8);
  selected_tile_ctx.putImageData(ci, 0, 0);

  var imageObject=new Image();
  imageObject.onload=function(){
    selected_tile_ctx.save();
    selected_tile_ctx.scale(10,10);
    selected_tile_ctx.fillStyle='#6a6a6a';
    selected_tile_ctx.fillRect(0,0,selected_tile_canvas.width,selected_tile_canvas.height);
    selected_tile_ctx.drawImage(imageObject,0,0);
    selected_tile_ctx.restore();
  }
  imageObject.src=selected_tile_canvas.toDataURL();

  showPalettes(tile_y, tile_x);

}