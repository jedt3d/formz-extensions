// Render SVG icon masters to formZ's icon format.
// usage: swift svg2bmp.swift <out-dir> <pixels> <master.svg>...
// Writes <name>.ENU.bmp (40-byte header, 32-bit BGRA, straight alpha,
// bottom-up) and <name>.png for previews. Uses AppKit's SVG support only.
import AppKit

let args = CommandLine.arguments
guard args.count >= 4, let px = Int(args[2]) else {
  FileHandle.standardError.write("usage: svg2bmp.swift <out-dir> <pixels> <master.svg>...\n".data(using: .utf8)!)
  exit(2)
}
let outDir = URL(fileURLWithPath: args[1])
try FileManager.default.createDirectory(at: outDir, withIntermediateDirectories: true)

func le32(_ v: Int) -> [UInt8] { (0..<4).map { UInt8((v >> (8 * $0)) & 0xff) } }
func le16(_ v: Int) -> [UInt8] { (0..<2).map { UInt8((v >> (8 * $0)) & 0xff) } }

for path in args.dropFirst(3) {
  let name = URL(fileURLWithPath: path).deletingPathExtension().lastPathComponent
  guard let svg = NSImage(contentsOfFile: path) else { print("\(name): cannot load"); exit(1) }
  let rep = NSBitmapImageRep(bitmapDataPlanes: nil, pixelsWide: px, pixelsHigh: px, bitsPerSample: 8,
    samplesPerPixel: 4, hasAlpha: true, isPlanar: false, colorSpaceName: .deviceRGB,
    bytesPerRow: px * 4, bitsPerPixel: 32)!
  NSGraphicsContext.saveGraphicsState()
  NSGraphicsContext.current = NSGraphicsContext(bitmapImageRep: rep)
  NSGraphicsContext.current!.imageInterpolation = .high
  svg.draw(in: NSRect(x: 0, y: 0, width: px, height: px))
  NSGraphicsContext.restoreGraphicsState()

  // rep holds premultiplied RGBA, top row first; formZ wants straight BGRA, bottom row first.
  let src = rep.bitmapData!
  var body = [UInt8](repeating: 0, count: px * px * 4)
  for y in 0..<px {
    for x in 0..<px {
      let s = (y * px + x) * 4
      let d = ((px - 1 - y) * px + x) * 4
      let a = Int(src[s + 3])
      func straight(_ c: UInt8) -> UInt8 { a == 0 ? 0 : UInt8(min(255, (Int(c) * 255 + a / 2) / a)) }
      body[d] = straight(src[s + 2]); body[d + 1] = straight(src[s + 1])
      body[d + 2] = straight(src[s]); body[d + 3] = UInt8(a)
    }
  }
  var bmp: [UInt8] = Array("BM".utf8) + le32(54 + body.count) + le32(0) + le32(54)
  bmp += le32(40) + le32(px) + le32(px) + le16(1) + le16(32) + le32(0) + le32(body.count)
  bmp += le32(2835) + le32(2835) + le32(0) + le32(0) + body
  try Data(bmp).write(to: outDir.appendingPathComponent("\(name).ENU.bmp"))
  try rep.representation(using: .png, properties: [:])!.write(to: outDir.appendingPathComponent("\(name).png"))
  print("\(name): \(px) px")
}
