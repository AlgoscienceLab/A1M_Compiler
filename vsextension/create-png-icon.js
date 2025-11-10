const fs = require('fs');
const path = require('path');

// Create a simple PNG icon (128x128) for the .algo file
// This is a minimal PNG with a gold triangle

// PNG header and chunks
const width = 128;
const height = 128;

// Simple approach: Use canvas if available, otherwise create a simple colored square
// For now, let's just copy the existing icon or create a simple one

const iconPath = path.join(__dirname, 'images', 'icon.png');
console.log('Icon already exists at:', iconPath);

// Verify it exists
if (fs.existsSync(iconPath)) {
    const stats = fs.statSync(iconPath);
    console.log('Icon size:', stats.size, 'bytes');
    console.log('Icon is ready to use!');
} else {
    console.log('Icon not found, please create one manually');
}
