original_canvas = null;
original_ctx = null;
tiles_canvas = null;
tiles_ctx = null;
final_palette_canvas = null;
final_palette_ctx = null;
palettes_canvas = null;
palettes_ctx = null;
unique_colors = new Array();
unique_colors_counter = new Array();
unique_sorted_colors = new Array();
image_loaded = false;
var original_image = null;

tile_canvas_buttons = [
  {x: 300, y: 10, w: 300, h: 30,
   mouse_out: function(){},
   mouse_over: function(){},
   on_mouse_down: function() {},
   on_mouse_up: function() {},
   button_state: false},
];

var color_1 = null;
var color_2 = null;
var color_3 = null;
var color_4 = null;

var final_palette_color_1 = "white";
var final_palette_color_2 = "white";
var final_palette_color_3 = "white";
var final_palette_color_4 = "white";

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
  tiles_canvas.width  = document.getElementById('png_holder').clientWidth;
  tiles_canvas.height = document.getElementById('png_holder').clientHeight;
  tiles_ctx = tiles_canvas.getContext('2d');
  tiles_ctx.fillStyle='black';
  tiles_ctx.scale(2,2);
  tiles_ctx.imageSmoothingEnabled = false;
  tiles_ctx.fillRect(0,0,tiles_canvas.width,tiles_canvas.height);

  palettes_canvas = document.getElementById("palettes");
  palettes_canvas.width  = document.getElementById('palettes_holder').clientWidth;
  palettes_ctx = palettes_canvas.getContext('2d');
  palettes_ctx.fillStyle='black';
  palettes_ctx.imageSmoothingEnabled = false;
  palettes_ctx.fillRect(0,0,palettes_canvas.width,palettes_canvas.height);

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

  color_1 = document.getElementById("final_color_1");
  color_1.addEventListener("input", function(){
    final_palette_color_1 = color_1.value;
    showFinalPalette();
  }, false);
  color_2 = document.getElementById("final_color_2");
  color_2.addEventListener("input", function(){
    final_palette_color_2 = color_2.value;
    showFinalPalette();
  }, false);
  color_3 = document.getElementById("final_color_3");
  color_3.addEventListener("input", function(){
    final_palette_color_3 = color_3.value;
    showFinalPalette();
  }, false);
  color_4 = document.getElementById("final_color_4");
  color_4.addEventListener("input", function(){
    final_palette_color_4 = color_4.value;
    showFinalPalette();
  }, false);
}

function showImage(fileReader) {
  var img = document.getElementById("hidden_image");
  img.onload = () => {
    getImageData(img);
    showTiles(img, 1);
    showPalettes(img);
    showFinalPalette();
    image_loaded = true;
  }
  img.src = fileReader.result;
}

function getImageData(img) {
  original_image = img;
  original_ctx.drawImage(original_image, 0, 0);
  imageData = original_ctx.getImageData(0, 0, original_image.width, original_image.height).data;

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


}

function showTiles(img, scale) {
  tile_size = 8 * scale
  space = (1 * scale)
  for (var i = 0; i < img.width/tile_size; i++) {
    for (var j = 0; j < img.height/tile_size; j++) {
      tiles_ctx.drawImage(img, i*tile_size, j*tile_size, tile_size,
                          tile_size, i*(tile_size + space), j*(tile_size + space), tile_size, tile_size);
    }
  }
}

function showPalettes() {
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
  var horizontal_counter = 20;
  var vertical_counter = 20;
  var colors = [final_palette_color_1, final_palette_color_2, final_palette_color_3, final_palette_color_4]
  for (var i = 0; i < 4; i++) {
    final_palette_ctx.fillStyle = colors[i]
    final_palette_ctx.fillRect(horizontal_counter, vertical_counter, 100, 100);

    final_palette_ctx.font="10px helvetica";
    final_palette_ctx.shadowColor="black";
    final_palette_ctx.shadowBlur = 3;
    final_palette_ctx.lineWidth = 2;
    final_palette_ctx.strokeText(i, horizontal_counter + 5, vertical_counter + 15);
    final_palette_ctx.shadowBlur = 0;
    final_palette_ctx.fillStyle="white";
    final_palette_ctx.fillText(i, horizontal_counter + 5, vertical_counter + 15);

    horizontal_counter += 110;
    if (horizontal_counter >= palettes_canvas.width || horizontal_counter + 100 >= palettes_canvas.width) {
      vertical_counter += 110;
      horizontal_counter = 20;
    }
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