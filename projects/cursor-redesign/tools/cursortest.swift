// Loads a file exactly as libFZRT fzrt_curs_make_cursor does, then renders the
// resulting NSCursor image into 1x (32 px) and 2x (64 px) bitmaps.
import AppKit
let out = CommandLine.arguments[1]
for p in CommandLine.arguments.dropFirst(2) {
  let name = ((p as NSString).lastPathComponent as NSString).deletingPathExtension
  guard let img = NSImage(contentsOfFile: p), img.isValid else { print(name, "load failed"); continue }
  img.size = NSSize(width: 32, height: 32)                       // setSize:(32,32)
  let cur = NSCursor(image: img, hotSpot: NSPoint(x: 7, y: 7))   // initWithImage:hotSpot:
  var line = "\(name): reps=" + img.representations.map { "\($0.pixelsWide)px" }.joined(separator: "+")
  for scale in [1, 2] {
    let px = 32 * scale
    let rep = NSBitmapImageRep(bitmapDataPlanes: nil, pixelsWide: px, pixelsHigh: px, bitsPerSample: 8,
      samplesPerPixel: 4, hasAlpha: true, isPlanar: false, colorSpaceName: .deviceRGB, bytesPerRow: 0, bitsPerPixel: 0)!
    rep.size = NSSize(width: 32, height: 32)
    NSGraphicsContext.saveGraphicsState()
    NSGraphicsContext.current = NSGraphicsContext(bitmapImageRep: rep)
    NSGraphicsContext.current!.imageInterpolation = .high
    cur.image.draw(in: NSRect(x: 0, y: 0, width: 32, height: 32))
    NSGraphicsContext.restoreGraphicsState()
    // crispness: share of visible pixels whose alpha is fully opaque (blur lowers it)
    var vis = 0, solid = 0
    for y in 0..<px { for x in 0..<px { let a = rep.colorAt(x: x, y: y)!.alphaComponent
      if a > 0.02 { vis += 1; if a > 0.98 { solid += 1 } } } }
    let used = cur.image.bestRepresentation(for: NSRect(x: 0, y: 0, width: 32, height: 32), context: nil,
      hints: [.ctm: AffineTransform(scale: CGFloat(scale))])!.pixelsWide
    line += String(format: " | %dx: uses %dpx, solid %.0f%%", scale, used, vis > 0 ? 100.0 * Double(solid) / Double(vis) : 0)
    try! rep.representation(using: .png, properties: [:])!.write(to: URL(fileURLWithPath: "\(out)/\(name)@\(scale)x.png"))
  }
  print(line)
}
