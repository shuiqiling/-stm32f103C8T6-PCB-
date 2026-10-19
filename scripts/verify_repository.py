"""Check the unpacked Keil project and hardware delivery without an ARM compiler."""
import hashlib
import json
import re
import sys
import zipfile
from pathlib import Path, PureWindowsPath
from urllib.parse import unquote, urlsplit
from xml.etree import ElementTree as ET

ROOT = Path(__file__).resolve().parents[1]
FIRMWARE = ROOT / 'firmware'
errors = []


def exact_path(path):
    """Check spelling/case as well as existence, including on Windows."""
    if not path.is_relative_to(ROOT):
        return False
    current = ROOT
    for part in path.relative_to(ROOT).parts:
        if not current.is_dir() or part not in {p.name for p in current.iterdir()}:
            return False
        current = current / part
    return current.exists()


def project_path(value):
    windows_path = PureWindowsPath(value)
    if windows_path.is_absolute() or windows_path.drive or '..' in windows_path.parts:
        errors.append('Non-portable project path: ' + value)
        return None
    return FIRMWARE.joinpath(*windows_path.parts)


project = ET.parse(FIRMWARE / 'projects.uvprojx')
refs = [node.text for node in project.iter('FilePath') if node.text]
include_dirs = []
for node in project.iter('IncludePath'):
    for value in (node.text or '').split(';'):
        if not value:
            continue
        path = project_path(value)
        if path is not None:
            include_dirs.append(path)
            if not exact_path(path):
                errors.append('Missing include directory: ' + value)

definitions = project.findtext('.//Cads/VariousControls/Define', '')
for required in ['STM32F10X_MD', 'USE_STDPERIPH_DRIVER']:
    if required not in re.split(r'[,;\s]+', definitions):
        errors.append('Missing target definition: ' + required)

sources = []
for value in refs:
    path = project_path(value)
    if path is None:
        continue
    if not exact_path(path):
        errors.append('Missing or incorrectly cased project file: ' + value)
    else:
        sources.append(path)

include_count = 0
for source in sources:
    if source.suffix.lower() not in {'.c', '.h', '.s'}:
        continue
    text = source.read_text(encoding='utf-8-sig')
    for name in re.findall(r'^\s*#\s*include\s*"([^"]+)"', text, flags=re.MULTILINE):
        include_count += 1
        if not any(exact_path(base / name) for base in [source.parent, *include_dirs]):
            errors.append(f'Unresolved quoted include in {source.relative_to(ROOT)}: {name}')

for stage in ['BeforeMake', 'BeforeCompile', 'AfterMake']:
    for node in project.findall('.//' + stage):
        if any(node.findtext(tag, '0') != '0' for tag in ['RunUserProg1', 'RunUserProg2']):
            errors.append('Unexpected enabled custom build command: ' + stage)

for path in FIRMWARE.rglob('*'):
    if path.is_file() and (
        path.suffix.lower() in {'.o', '.d', '.crf', '.axf', '.map', '.lst', '.dep', '.uvoptx', '.bat'}
        or any(part in {'Objects', 'Listings'} for part in path.parts)
        or '.uvguix.' in path.name
    ):
        errors.append('Generated or machine-local file in firmware: ' + str(path.relative_to(ROOT)))

manifest = json.loads((ROOT / 'docs/import-manifest.json').read_text(encoding='utf-8'))
hardware_count = 0
for record in manifest['files']:
    if not record.get('bytesPreserved'):
        continue
    path = ROOT / record['path']
    hardware_count += 1
    if not path.is_file() or hashlib.sha256(path.read_bytes()).hexdigest() != record['sha256']:
        errors.append('Hardware file differs from imported source: ' + record['path'])

for relative in ['hardware/gerber/board-gerber.zip', 'archive/超声波智能避障小车.zip']:
    try:
        with zipfile.ZipFile(ROOT / relative) as archive:
            bad = archive.testzip()
            if bad:
                errors.append('Archive CRC failure: ' + relative + ':' + bad)
    except (OSError, zipfile.BadZipFile) as error:
        errors.append('Invalid archive: ' + relative + ': ' + str(error))

link_count = 0
for markdown in ROOT.rglob('*.md'):
    for match in re.findall(r'!?\[[^\]]*\]\(([^)]+)\)', markdown.read_text(encoding='utf-8')):
        url = match.strip('<>').split(' "', 1)[0]
        parsed = urlsplit(url)
        if parsed.scheme or not parsed.path:
            continue
        link_count += 1
        target = (markdown.parent / unquote(parsed.path)).resolve()
        if not exact_path(target):
            errors.append(f'Broken relative link in {markdown.relative_to(ROOT)}: {url}')

report = {
    'projectFileReferences': len(refs),
    'quotedIncludesChecked': include_count,
    'hardwareFilesVerified': hardware_count,
    'relativeLinksChecked': link_count,
    'errors': errors,
    'crossCompilationPerformed': False,
    'hardwareRuntimeTestPerformed': False,
}
print(json.dumps(report, ensure_ascii=False, indent=2))
sys.exit(bool(errors))
